#include "../include/Model/Employee.h"
std::optional<Model::Employee> updateEmpViewer();

bool Model::Employee::viewEmployee() {
	try {
		system("cls");
		std::string query;
		auto tmp = viewEmp();
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

bool Model::Employee::insertEmployee() {
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
			std::cout << "\x1b[32mEmployee inserted successfully\x1b[0m\n";
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

bool Model::Employee::updateEmployee() {
	try {

		auto tmp = updateEmpViewer();
		if (tmp.has_value()) {

			*this = tmp.value();

			std::string query =  " UPDATE Department SET  firstname='" + firstname + "', lastname='" + lastname + "', dob='" + dob + "', mobile='" + mobile + "', email='" + email + "', address='" + address + "'WHERE id = " + std::to_string(Eid) + ";";

			std::cout << query << "\n";
			waitMenu();
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
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
		waitMenu();
		return false;
	}
}

bool Model::Employee::deleteEmployee() {
	try {
		system("cls");
		std::string query1 = "delete from Employee where ";
		std::string s;
		int count1 = 0;
		int count2 = 0;
		int i;
		std::cout << "Select the Field on which you want to perform delete Operation\n";
		std::cout << "0. Go Back\n";
		std::cout << "1. Eid\n";
		std::cout << "2. email\n\n";

		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-2]" }).value_or("0"));
		std::cout << "\n";
		std::string tmp;
		while (1) {
			switch (i) {
			case 0:
				return true;

			case 1:
				if (auto tmp = input("Enter Eid: ", idRegex); tmp.has_value()) setId(std::stoi(tmp.value()));
				else {
					std::cout << "\x1b[33m Deletion Failed!!! \x1b[0m\n";
					waitMenu();
					return false;
				}
				query1 += "Eid = " + std::to_string(getId()) + ";";
				break;

			case 2:
				if (auto tmp = input("Enter Email: ", emailRegex); tmp.has_value()) setEmail(tmp.value());
				else {
					std::cout << "\x1b[33m Deletion Failed!!! \x1b[0m\n";
					waitMenu();
					return false;
				}
				query1 += "email = '" + getEmail() + "';";
				break;

			default:
				std::cout << "Enter valid field to delete\n";
				deleteEmployee();
				break;
			}
			break;
		}
		//std::cout << query1 << "\n";

		int rc = DB::Database::getInstance().executeQuery(query1.c_str());
		if (rc == 0) {
			int change = sqlite3_changes(DB::Database::getInstance().db);
			if (change == 0) {
				std::cout << "\x1b[33mSelected Employee is not in database\x1b[0m\n";
				waitMenu();
				return false;
			}
			else {
				std::cout << "\x1b[32mEmployee Deleted successfully\x1b[0m\n\n";
				waitMenu();
				logging::Info("Employee deleted for Id: ", std::to_string(getId()));
				return true;
			}
		}
		else if (rc == 19) {
			std::cout << "\x1b[33mYou can not delete this Employee because this is a manager of other employees \x1b[0m\n\n";
			waitMenu();
			return false;
		}
		return false;

	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "\x1b[33m Deletion Failed!!! \x1b[0m\n";
		waitMenu();
		return false;
	}
	return false;
}

void Model::Employee::action() noexcept {

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
		//d1->setGender(static_cast<Gender>(argv[7] )? argv[7] : "");
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

	//std::cout << d.getManagerId() << "\n";
	//waitMenu();
	std::cout << e.getId();
	return e;
}

//bool Model::Employee::userInputEmployee() {
//	/*try {
//
//		std::string msg = " Enter # to leave the field Empty: \n";
//
//		if (auto tmp = input("Enter Eid: ", idRegex); tmp.has_value()) setId(std::stoi(tmp.value()));
//		else return false;
//
//		if (auto tmp = input("Enter FirstName OR " + msg, alphaRegex); tmp.has_value()) setFirstname(tmp.value());
//		else return false;
//
//		if (auto tmp = input("Enter LastName OR " + msg, alphaRegex); tmp.has_value()) setLastname(tmp.value());
//		else return false;
//
//		if (auto tmp = input("Enter DOB (dd-mm-yyyy) OR " + msg, dateRegex); tmp.has_value()) setDob(tmp.value());
//		else return false;
//
//		if (auto tmp = input("Enter Mobile OR " + msg, mobileRegex); tmp.has_value()) setMobile(tmp.value());
//		else return false;
//
//		if (auto tmp = input("Enter Email OR " + msg, emailRegex); tmp.has_value()) setEmail(tmp.value());
//		else return false;
//
//		if (auto tmp = input("Enter Email OR " + msg, allRegex); tmp.has_value()) setAddress(tmp.value());
//		else return false;
//
//		auto gender = input("Enter Gender(Male / Female / Other): ", genderRegex);
//		if (gender.has_value()) {
//			if (gender.value() == "Male") {
//				setGender(Gender::Male);
//			}
//			else if (gender.value() == "Female") {
//				setGender(Gender::Female);
//			}
//			else {
//				setGender(Gender::Other);
//			}
//		}
//		else {
//			return false;
//		}
//
//		if (auto tmp = input("Enter DOJ(dd-mm-yyyy) OR " + msg, dateRegex); tmp.has_value()) setDoj(tmp.value());
//		else return false;
//
//		if (auto tmp = input("Enter Manager Id: ", idRegex); tmp.has_value()) setManagerId(stoi(tmp.value()));
//		else return false;
//
//		if (auto tmp = input("Enter Department Id: ", idRegex); tmp.has_value()) setDepartmentId(stoi(tmp.value()));
//		else return false;
//
//		return s.userInputSalary();
//
//	}
//	catch (std::exception& e) {
//		std::cout << e.what() << std::endl;
//		waitMenu();
//		return false;
//	}*/
//}