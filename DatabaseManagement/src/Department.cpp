#include "../include/Model/Department.h"
<<<<<<< HEAD
#include "../include/controllers/departmentController.h"

bool Model::Department::viewDepartment() const {
=======
#include "../include/Views/DeptView.h"


inline std::optional<std::pair<std::string, std::string>> viewDept();
bool Model::Department::viewDepartment() {
>>>>>>> 17217775496b21dd86a60f626a1c9ac79568d942
	try {
		system("cls");

		std::string query;
<<<<<<< HEAD
		auto tmp = viewDepartmentController();
=======
		auto tmp = viewDept();
>>>>>>> 17217775496b21dd86a60f626a1c9ac79568d942

		if (tmp.has_value()) {
			auto& [field, value] = tmp.value();
			if (field == "id" || field == "manager_id") {

				query += "select * from Department where " + field + " = " + value + " ;";
			}
			else if (field == "all") {
				query += "select * from Department ;";
			}
			else {
				query += "select * from Department where " + field + " = '" + value + "' ;";
<<<<<<< HEAD
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

bool Model::Department::insertDepartment() const {
=======
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

bool Model::Department::insertDepartment() {
>>>>>>> 17217775496b21dd86a60f626a1c9ac79568d942
	try {
		//system("cls");

		std::string query = "INSERT INTO Department "
			"(id, Dname, manager_id, description) "
			"VALUES (" + std::to_string(Did) + ", '" + Dname + "'," + std::to_string(manager_id) + ", '" + description + "');";
		//std::cout << query;   
		int rc = DB::Database::getInstance().executeQuery(query.c_str());
		if (rc == 19) {
			std::cout << "\x1b[33mEntered manager is not available in particular table OR Entered department ID is already exist in table  \x1b[0m\n\n";
			waitMenu();
			return false;
		}
		else if (rc == 0) {
			std::cout << "\x1b[32mDepartment added successfully\x1b[0m \n\n";
			waitMenu();
			logging::Info("Department added for Id: ", std::to_string(getId()));
			return true;
		}
		return false;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

bool Model::Department::updateDepartment() const {

	try {

<<<<<<< HEAD
		//  for testing 
		std::string select = "select * from Department where id = " + std::to_string(getId()) + ";";

		DB::Database::getInstance().selectQueryForChecking(select.c_str());

		if (DB::Database::row == 0) {
			std::cout << "\x1b[33m Department is not in database \x1b[0m\n";
			waitMenu();
			return false;
		}
		std::string query = "update Department set Dname = '" + Dname + "', manager_id = " + std::to_string(manager_id) + ", description =  '" + description + "' where id = " + std::to_string(Did) + "; ";
		//std::cout << query << "\n";
		//waitMenu();
		int rc = DB::Database::getInstance().executeQuery(query.c_str());

		if (rc == 19) {
			std::cerr << "\x1b[33m You can not assigne value because entered manager is not in database \x1b[0m\n\n";
			waitMenu();
			return false;
		}
		else if (rc == 0) {
			std::cout << "\x1b[32mDepartment Updated successfully\x1b[0m \n\n";
			waitMenu();
			logging::Info("Department Updated with Id: ", std::to_string(getId()));
			return true;
		}
		return false;
=======
		// Uncomment for testing
		/*std::string select = "select * from Department where id = " + std::to_string(getId()) + ";";

		DB::Database::getInstance().selectQuery(select.c_str());

		if (DB::Database::row == 0) {
			std::cout << "\x1b[33m Department is not in database \x1b[0m\n";
			waitMenu();
			return false;
		}*/
		std::string query = "update Department set Dname = '" + Dname + "', manager_id = " + std::to_string(manager_id) + ", description =  '" + description + "' where id = " + std::to_string(Did) + "; ";
		//std::cout << query << "\n";
		//waitMenu();
		int rc = DB::Database::getInstance().executeQuery(query.c_str());

		if (rc == 19) {
			std::cerr << "\x1b[33m You can not assigne value because entered manager is not in database \x1b[0m\n\n";
			waitMenu();
			return false;
		}
		else if (rc == 0) {
			std::cout << "\x1b[32mDepartment Updated successfully\x1b[0m \n\n";
			waitMenu();
			logging::Info("Department Updated with Id: ", std::to_string(getId()));
			return true;
		}

>>>>>>> 17217775496b21dd86a60f626a1c9ac79568d942
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
		waitMenu();
		return false;
	}
}

<<<<<<< HEAD
bool Model::Department::deleteDepartment() const {
=======
bool Model::Department::deleteDepartment() {
>>>>>>> 17217775496b21dd86a60f626a1c9ac79568d942
	try {
		std::string query = "delete from Department where id = " + std::to_string(Did) + ";";

		int rc = DB::Database::getInstance().executeQuery(query.c_str());
		if (rc == 0) {
			int change = sqlite3_changes(DB::Database::getInstance().db);
			if (change == 0) {
				std::cout << "\x1b[33mSelected Department is not in database\x1b[0m\n";
				waitMenu();
				return false;
			}
			else {
				std::cout << "\x1b[32mDepartment Deleted successfully\x1b[0m \n\n";
				waitMenu();
				logging::Info("Department Deleted with Id: ", std::to_string(getId()));
				return true;
			}
		}
		else if (rc == 19) {
			std::cout << "\x1b[33mYou can not Delete this department because there is employee which are working in this department \x1b[0m \n\n";
			waitMenu();
			return false;
		}

	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "\x1b[33m Deletion Failed!!! \x1b[0m\n";
		waitMenu();
		return false;
	}
}

std::optional<Model::Department> Model::Department::getDepartment(const std::string& id) {
	Department d;
	try {
		auto callback = [](void* data, int argc, char** argv, char** azColName) {
			Department* d1 = static_cast<Department*>(data);
			d1->setId(argv[0] ? std::stoi(argv[0]) : throw "1");
			d1->setName(argv[1] ? argv[1] : throw "1");
			d1->setManagerId(argv[2] ? std::stoi(argv[2]) : throw "");
			d1->setDescription(argv[3] ? argv[3] : throw "");
			return 0;
			};

		std::string selectQuery = "SELECT * FROM Department WHERE id = " + id + ";";

		sqlite3_exec(DB::Database::getInstance().db, selectQuery.c_str(), callback, &d, 0);
		return d;
	}
	catch (...) {
		std::cout << "Throw" << "\n";
		waitMenu();
		return std::nullopt;
	}
}