#include "../include/Model/Employee.h"

bool Model::Employee::viewEmployee() {

	try {

		std::string query = "select * from Employee where ";
		std::string all = "";
		std::string join = "";
		std::cout << "Select the Field on which you want to view the Employee\n";
		std::cout << "0. Go Back\n";
		std::cout << "1. Eid\n";
		std::cout << "2. fname\n";
		std::cout << "3. email\n";
		std::cout << "4. department name\n";
		std::cout << "5. Manager Id\n";
		std::cout << "6. ALL\n\n";
		int i;
		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-6]" }).value_or("0"));
		std::string tmp;
		while (1) {
			switch (i) {
			case 0:
				return true;

			case 1:
				std::cout << "Enter Eid: ";
				std::cin >> tmp;
				query += "Eid = " + tmp + ";";
				DB::Database::getInstance().selectQuery(query.c_str());
				break;
			case 2:
				std::cout << "Enter fname: ";
				std::cin >> tmp;
				query += "firstname = '" + tmp + "';";
				DB::Database::getInstance().selectQuery(query.c_str());
				break;
			case 3:
				std::cout << "Enter email: ";
				std::cin >> tmp;
				query += "email = '" + tmp + "';";
				DB::Database::getInstance().selectQuery(query.c_str());
				break;
			case 4:
				std::cout << "Enter departmaent name: ";
				std::cin >> tmp;
				join += "SELECT Employee.* FROM Employee JOIN Department ON Employee.department_id = Department.id WHERE Dname = '" + tmp + "' ;";
				//std::cout << join;
				DB::Database::getInstance().selectQuery(join.c_str());
				break;
			case 5:
				std::cout << "Enter Manager Id: ";
				std::cin >> tmp;
				query += "manager_id = '" + tmp + "';";
				DB::Database::getInstance().selectQuery(query.c_str());
				break;
			case 6:
				all += "select * from Employee";
				DB::Database::getInstance().selectQuery(all.c_str());
				break;
			default:
				std::cout << "Enter valid field\n";
				viewEmployee();
				break;
			}
			break;
		}
		if (DB::Database::row == 0) {
			std::cout << "\x1b[38;5;208mEmployee Not Available\x1b[0m\n";
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
			std::cout << "Employee inserted successfully\n";
			logging::Info("Employee added for Id: ", std::to_string(getId()));
			s.insertSalary(getId());
			return true;
		}
		else if (rc == 19) {
			std::cout << "Entered manager or department is not available in particular table Or entered employee is already exist \n\n";
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
		std::string query = "update Employee set ";
		setId(std::stoi(input("Enter the Eid to update Employee : ", idRegex).value()));

		std::string select = "select * from Employee where Eid = " + std::to_string(getId()) + " ;";
		DB::Database::getInstance().selectQuery(select.c_str());
		if (DB::Database::row == 0) {
			std::cout << "Entered Employee is not in database\n\n";
			std::cout << "Press 0 to continue\n";
			int i;
			std::cin >> i;
			return false;
		}
		else {
			std::unordered_map<std::string, std::string> mp;
			bool check = true;
			int i;
			while (check) {
				std::cout << "Select the field you want to update \n";
				std::cout << "0. Go Back\n";
				std::cout << "1. FirstName\n";
				std::cout << "2. lastName\n";
				std::cout << "3. DOB\n";
				std::cout << "4. mobile\n";
				std::cout << "5. email\n";
				std::cout << "6. address\n";
				std::cout << "7. gender\n";
				std::cout << "8. doj\n";
				std::cout << "9. managerId\n";
				std::cout << "10. departmentId\n";
				std::cout << "11. toUpdateDatabase\n";
				std::string value;
				i = std::stoi(input("Enter Your Choice : ", std::regex{ "^[0-9]$|^1[0-1]$" }).value_or("0"));
				switch (i) {
				case 0:
					return true;

				case 1:
					//setFirstname(input("Enter firstname: ", alphaRegex).value());
					mp.insert({ "firstname" , firstname });
					break;

				case 2:
					//setLastname(input("Enter LastName: " , alphaRegex).value());
					mp.insert({ "lastname" ,  lastname });
					break;

				case 3:
					//setDob(input("Enter DOB (dd-mm-yyyy): " , dateRegex).value());
					mp.insert({ "dob" , dob });
					break;

				case 4:
					//setMobile(input("Enter Mobile: " , mobileRegex).value());
					mp.insert({ "mobile" , mobile });
					break;

				case 5:
					//setEmail(input("Enter Email: ", emailRegex).value());
					mp.insert({ "email" , email });
					break;

				case 6:
					//setAddress();
					mp.insert({ "address" , address });
					break;

				case 7:
					/*value = input("Enter Gender (Male/Female/Other: )", genderRegex).value();
					mp.insert({ "gender" , value });*/
					mp.insert({ "gender" , "Male" });
					break;

				case 8:
					//setDoj(input("Enter DOJ(dd-mm-yyyy): ", dateRegex).value());
					mp.insert({ "doj" , doj });
					break;

				case 9:
					//setManagerId(stoi(input("Enter Manager Id: ", idRegex).value())); 
					mp.insert({ "manager_id" , std::to_string(manager_id) });
					break;

				case 10:
					//setDepartmentId(stoi(input("Enter Department Id: ", idRegex).value())); 
					mp.insert({ "department_id" , std::to_string(department_id) });
					break;

				case 11:
					check = false;
					break;
				}
			}

			auto itr = mp.end();
			if (mp.size() != 0) itr--;

			for (auto it = mp.begin(); it != mp.end(); ++it) {

				auto& [field, value] = *it;

				query += field + " = ";
				if (field == "manager_id" || field == "department_id") {
					query += value + " ";
				}
				else {
					query += "'" + value + "' ";
				}

				if (it != itr)
					query += ",";
			}
			query += "where Eid = " + std::to_string(getId()) + " ;";

			//std::cout << query << "\n";

			int rc = DB::Database::getInstance().executeQuery(query.c_str());
			if (rc == 0) {
				std::cout << "Employee updated successfully\n\n";
				waitMenu();
				logging::Info("Employee updated for Id: ", std::to_string(getId()));
				return true;
			}
			else if (rc == 19) {
				std::cout << "You can not assign value beacuse entered manager or department is not in particular table\n\n";
				waitMenu();
				return false;
			}
			return false;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "\x1b[33mUpdation Failed!!! \x1b[0m\n";
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
				setId(std::stoi(input("Enter Eid: ", idRegex).value()));
				query1 += "Eid = " + std::to_string(getId()) + ";";
				break;

			case 2:
				setEmail(input("Enter email: ", emailRegex).value());
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
				std::cout << "Selected Employee is not in database\n";
				waitMenu();
				return false;
			}
			else {
				std::cout << "Employee Deleted successfully\n\n";
				waitMenu();
				logging::Info("Employee deleted for Id: ", std::to_string(getId()));
				return true;
			}
			return false;
		}
		else if (rc == 19) {
			std::cout << "You can not delete this Employee because this is a manager of other employees \n\n";
			waitMenu();
			return false;
		}
		return false;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "\x1b[33mDeletion Failed!!! \x1b[0m\n";
		waitMenu();
		return false;
	}
}

void Model::Employee::action() noexcept {

}

bool Model::Employee::userInputEmployee() {
	try {

		std::string msg = " Enter # to leave the field Empty: \n";
		setId(stoi(input("Enter Eid: ", idRegex).value()));
		setFirstname(input("Enter FirstName OR " + msg, alphaRegex).value());
		setLastname(input("Enter LastName OR " + msg, alphaRegex).value());
		setDob(input("Enter DOB (dd-mm-yyyy) OR " + msg, dateRegex).value());
		setMobile(input("Enter Mobile OR " + msg, mobileRegex).value());
		setEmail(input("Enter Email OR " + msg, emailRegex).value());
		setAddress();

		string gender = input("Enter Gender(Male / Female / Other): ", genderRegex).value();
		if (gender == "Male") {
			setGender(Gender::Male);
		}
		else if (gender == "Female") {
			setGender(Gender::Female);
		}
		else {
			setGender(Gender::Other);
		}

		setDoj(input("Enter DOJ(dd-mm-yyyy) OR " + msg, dateRegex).value());
		setManagerId(stoi(input("Enter Manager Id: ", idRegex).value()));
		setDepartmentId(stoi(input("Enter Department Id: ", idRegex).value()));
		s.userInputSalary();
		return true;
	}
	catch (std::exception& e) {
		/*std::cout << e.what() << std::endl;
		waitMenu();*/
		return false;
	}
}