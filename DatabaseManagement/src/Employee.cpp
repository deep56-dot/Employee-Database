#include "../include/Model/Employee.h"
<<<<<<< HEAD
#include "../include/controllers/employeeController.h"
=======
#include "../include/Views/EmpView.h"


>>>>>>> 17217775496b21dd86a60f626a1c9ac79568d942

bool Model::Employee::viewEmployee() const {
	try {
		system("cls");
		std::string query;
		auto tmp = viewEmployeeController();
		if (tmp.has_value()) {
			auto& [field, value] = tmp.value();
			if (field == "Eid" || field == "manager_id") {

				query += "select * from Employee where " + field + " = " + value + " ;";
			}
			else if (field == "all") {
				query += "select * from Employee ;";
			}
			else if (field == "Dname") {
				query += "SELECT Employee.* FROM Employee JOIN Department ON Employee.department_id = Department.id WHERE Dname = '" + value + "' ;";
			}
			else {
				query += "select * from Employee where " + field + " = '" + value + "' ;";
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

bool Model::Employee::insertEmployee() const {
	try {

		std::string query = "INSERT INTO Employee "
			"(Eid, firstname, lastname, dob, mobile, email, address, gender, doj, manager_id, department_id) "
			"VALUES (" + std::to_string(Eid) + ", '" + firstname + "', '" + lastname + "', '" + dob + "', '" + mobile + "', '" + email + "', '" + address + "' , '";
		if (gender == Gender::Male) {
			query += "Male";
		}
		else if (gender == Gender::Female) {
			query += "Female";
		}
		else {
			query += "Other";
		}
		query += "' , '" + doj + "', " + std::to_string(manager_id) + ", " + std::to_string(department_id) + "); ";

		int rc = DB::Database::getInstance().executeQuery(query.c_str());
		if (rc == 0) {
			//std::cout << "\x1b[32mEmployee inserted successfully\x1b[0m\n";
			logging::Info("Employee added for Id: ", std::to_string(getId()));
			return s.insertSalary(getId());
		}
		else if (rc == 19) {
			std::cout << "\x1b[33mEntered manager or department is not available in particular table Or entered employee is already exist \x1b[0m\n\n";
			waitMenu();
			return false;
		}
		return true;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

bool Model::Employee::updateEmployee() const {
	try {

<<<<<<< HEAD
		//  for testing
		std::string select = "select * from Employee where Eid = " + std::to_string(Eid) + ";";

		DB::Database::getInstance().selectQueryForChecking(select.c_str());
		if (DB::Database::row == 0) {
			std::cout << "\x1b[33m Employee is not in database \x1b[0m\n";
			waitMenu();
			return false;
		}

		std::string query = " UPDATE Employee SET  firstname = '" + firstname + "', lastname = '" + lastname + "', dob = '" + dob + "', mobile = '" + mobile + "', email = '" + email + "', address = '" + address + "', gender = ";
		if (gender == Gender::Male) {
			query += "'Male'";
		}
		else if (gender == Gender::Female) {
			query += "'Female'";
		}
		else {
			query += "'Other'";
		}

		query += ", doj = '" + doj + "' , manager_id = " + std::to_string(manager_id) + " , department_id = " + std::to_string(department_id) + " WHERE Eid = " + std::to_string(Eid) + ";";
		//std::cout << query << "\n";
		//waitMenu(); 
		int rc = DB::Database::getInstance().executeQuery(query.c_str());

		if (rc == 19) {
			std::cerr << "\x1b[33m You can not assigne value because entered manager or department is not in database OR entered employee is already in database \x1b[0m\n\n";
			waitMenu();
			return false;
		}
		else if (rc == 0) {
			//std::cout << "\x1b[32m Employee Updated successfully\x1b[0m \n\n";
=======
		// Uncooment for testing
		/*std::string select = "select * from Employee where Eid = " + std::to_string(Eid) + ";";

		DB::Database::getInstance().selectQuery(select.c_str());
		if (DB::Database::row == 0) {
			std::cout << "\x1b[33m Employee is not in database \x1b[0m\n";
			waitMenu();
			return false;
		}*/

		std::string query = " UPDATE Employee SET  firstname = '" + firstname + "', lastname = '" + lastname + "', dob = '" + dob + "', mobile = '" + mobile + "', email = '" + email + "', address = '" + address + "', gender = ";
		if (gender == Gender::Male) {
			query += "'Male'";
		}
		else if (gender == Gender::Female) {
			query += "'Female'";
		}
		else {
			query += "'Other'";
		}

		query += ", doj = '" + doj + "' , manager_id = " + std::to_string(manager_id) + " , department_id = " + std::to_string(department_id) + " WHERE Eid = " + std::to_string(Eid) + ";";
		//std::cout << query << "\n";
		//waitMenu(); 
		int rc = DB::Database::getInstance().executeQuery(query.c_str());

		if (rc == 19) {
			std::cerr << "\x1b[33m You can not assigne value because entered manager or department is not in database OR entered employee is already in database \x1b[0m\n\n";
			waitMenu();
			return false;
		}
		else if (rc == 0) {
			std::cout << "\x1b[32m Employee Updated successfully\x1b[0m \n\n";
>>>>>>> 17217775496b21dd86a60f626a1c9ac79568d942
			waitMenu();
			logging::Info("Employee Updated with Id: ", std::to_string(getId()));
			return true;
		}
<<<<<<< HEAD
		return false;
=======

>>>>>>> 17217775496b21dd86a60f626a1c9ac79568d942
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
		waitMenu();
		return false;
	}

}

bool Model::Employee::deleteEmployee() const {
	try {
		std::string query = "delete from Employee where Eid = " + std::to_string(Eid) + ";";

		int rc = DB::Database::getInstance().executeQuery(query.c_str());

		if (rc == 0) {
			int change = sqlite3_changes(DB::Database::getInstance().db);
			if (change == 0) {
				std::cout << "\x1b[33m Selected Employee is not in database\x1b[0m\n";
				waitMenu();
				return false;
			}
			else {
<<<<<<< HEAD
				//std::cout << "\x1b[32m Employee Deleted successfully\x1b[0m \n\n";
=======
				std::cout << "\x1b[32m Employee Deleted successfully\x1b[0m \n\n";
>>>>>>> 17217775496b21dd86a60f626a1c9ac79568d942
				waitMenu();
				logging::Info("Employee Deleted with Id: ", std::to_string(getId()));
				return true;
			}
		}
		else if (rc == 19) {
			std::cout << "\x1b[33m You can not Delete this Employee because there is employee which are managed by in this Employee \x1b[0m \n\n";
			waitMenu();
			return false;
		}
<<<<<<< HEAD
		return false;
=======

>>>>>>> 17217775496b21dd86a60f626a1c9ac79568d942
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "\x1b[33m Deletion Failed!!! \x1b[0m\n";
		waitMenu();
		return false;
	}
}

std::optional<Model::Employee> Model::Employee::getEmployee(const std::string& id) {

	Employee e;
	auto callback = [](void* data, int argc, char** argv, char** azColName) {
		Employee* d1 = static_cast<Employee*>(data);
		d1->setId(argv[0] ? std::stoi(argv[0]) : -1);
		d1->setFirstname(argv[1] ? argv[1] : "");
		d1->setLastname(argv[2] ? argv[2] : "");
		d1->setDob(argv[3] ? argv[3] : "");
		d1->setMobile(argv[4] ? argv[4] : "");
		d1->setEmail(argv[5] ? argv[5] : "");
		d1->setAddress(argv[6] ? argv[6] : "");
		if (argv[7] == "Male") d1->setGender(Gender::Male);
		else if (argv[7] == "Female") d1->setGender(Gender::Female);
		else d1->setGender(Gender::Other);
		d1->setDoj(argv[8] ? argv[8] : "");
		d1->setManagerId(argv[9] ? std::stoi(argv[9]) : -1);
		d1->setDepartmentId(argv[10] ? std::stoi(argv[10]) : -1);

		return 0;
		};

	std::string selectQuery = "SELECT * FROM Employee WHERE Eid = " + id + ";";

	try {
		sqlite3_exec(DB::Database::getInstance().db, selectQuery.c_str(), callback, &e, 0);
	}
	catch (...) {
		return std::nullopt;
	}

	//std::cout << e.getId(); 
	return e;
}