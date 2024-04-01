#include "../include/Model/Engineer.h"
#include "../include/controllers/engineerController.h"

bool Model::Engineer::viewEngineer() const {
	try {
		system("cls");
		std::string query;

		auto tmp = viewEngineerController();

		if (tmp.has_value()) {
			auto& [field, value] = tmp.value();
			if (field == "Eid" || field == "manager_id") {

				query += "SELECT * FROM Employee INNER JOIN Engineer ON Engineer.id = Employee.Eid and " + field + " = " + value + " ;";
			}
			else if (field == "all") {
				query += "SELECT * FROM Employee INNER JOIN Engineer ON Engineer.id = Employee.Eid;";
			}
			else if (field == "Dname") {
				query += "SELECT e.*, eng.* FROM Employee e INNER JOIN Engineer eng ON e.Eid = eng.id INNER JOIN Department dept ON e.department_id = dept.id WHERE dept.Dname = '" + value + "' ;";
			}
			else {
				query += "SELECT * FROM Employee INNER JOIN Engineer ON Engineer.id = Employee.Eid and " + field + " = '" + value + "' ;";
			}

			DB::Database::getInstance().selectQuery(query.c_str());
			if (DB::Database::row == 0) {
				return false;
			}
			waitMenu();
			return true;
		}
		else {
			return false;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

bool Model::Engineer::insertEngineer() const {
	try {

		if (auto ch = insertEmployee(); ch) {
			std::string query = "";
			query += "INSERT INTO Engineer VALUES ( " + to_string(getId()) + ", ' " + programming_language + " ' , ' " + specialization + " ') ;";

			int rc = DB::Database::getInstance().executeQuery(query.c_str());

			if (rc == 0) {
				std::cout << "\x1b[32m Engineer Inserted successfully\x1b[0m\n\n";
				waitMenu();
				logging::Info("Engineer Added for Id: ", std::to_string(getId()));
				return true;
			}
			else if (rc == 19) {
				std::cout << "\x1b[33m Entered Enginner is already exist\x1b[0m\n\n";
				waitMenu();
				return false;
			}
		}
		else {
			return false;
		}
		return false;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
	return false;
}

bool Model::Engineer::updateEngineer() const {
	try {
		if (auto ch = updateEmployee(); ch) {

			std::string query = "update Engineer set programming_language = '" + programming_language + "' , specialization = '" + specialization + "' where id = " + std::to_string(getId()) + " ;";

			int rc = DB::Database::getInstance().executeQuery(query.c_str());

			if (rc == 0) {
				std::cout << "\x1b[32m Engineer updated successfully\x1b[0m\n\n";
				waitMenu();
				logging::Info("Engineer updated for Id: ", std::to_string(getId()));
				return true;
			}
			else if (rc == 19) {
				std::cout << "\x1b[33m  You can not assign value beacuse entered manager or department is not in particular table OR Engineer is already in database \x1b[0m\n\n";
				waitMenu();
				return false;
			}
			return false;
		}
		else {
			std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
			waitMenu();
			return false;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
		waitMenu();
		return false;
	}
	return false;
}

bool Model::Engineer::deleteEngineer() const {
	try {
		system("cls");
		return deleteEmployee();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

std::optional<Model::Engineer> Model::Engineer::getEngineer(const std::string& id) {

	Engineer e;
	auto callback = [](void* data, int argc, char** argv, char** azColName) {
		Engineer* e1 = static_cast<Engineer*>(data);
		e1->setId(argv[0] ? std::stoi(argv[0]) : -1);
		e1->setFirstname(argv[1] ? argv[1] : "");
		e1->setLastname(argv[2] ? argv[2] : "");
		e1->setDob(argv[3] ? argv[3] : "");
		e1->setMobile(argv[4] ? argv[4] : "");
		e1->setEmail(argv[5] ? argv[5] : "");
		e1->setAddress(argv[6] ? argv[6] : "");
		if (argv[7] == "Male") e1->setGender(Gender::Male);
		else if (argv[7] == "Female") e1->setGender(Gender::Female);
		else e1->setGender(Gender::Other);
		e1->setDoj(argv[8] ? argv[8] : "");
		e1->setManagerId(argv[9] ? std::stoi(argv[9]) : -1);
		e1->setDepartmentId(argv[10] ? std::stoi(argv[10]) : -1);
		e1->setProgramming_language(argv[12] ? argv[12] : "");
		e1->setSpecialization(argv[13] ? argv[13] : "");

		return 0;
		};

	std::string selectQuery = "SELECT * FROM Employee INNER JOIN Engineer ON Engineer.id = Employee.Eid and Employee.Eid = " + id + " ;";

	try {
		sqlite3_exec(DB::Database::getInstance().db, selectQuery.c_str(), callback, &e, 0);
	}
	catch (...) {
		return std::nullopt;
	}

	//std::cout << e.getId(); 
	return e;
}