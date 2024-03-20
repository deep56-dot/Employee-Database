#include "../include/Model/Employee.h"

bool Employee::viewEmployee() {

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
		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-6]" }));
		std::string tmp;
		while (1) {
			switch (i) {
			case 0:
				return true;

			case 1:
				std::cout << "Enter Eid: ";
				std::cin >> tmp;
				query += "Eid = " + tmp + ";";
				Database::getInstance().selectQuery(query.c_str());
				break;
			case 2:
				std::cout << "Enter fname: ";
				std::cin >> tmp;
				query += "firstname = '" + tmp + "';";
				Database::getInstance().selectQuery(query.c_str());
				break;
			case 3:
				std::cout << "Enter email: ";
				std::cin >> tmp;
				query += "email = '" + tmp + "';";
				Database::getInstance().selectQuery(query.c_str());
				break;
			case 4:
				std::cout << "Enter departmaent name: ";
				std::cin >> tmp;
				join += "SELECT Employee.* FROM Employee JOIN Department ON Employee.department_id = Department.id WHERE Dname = '" + tmp + "' ;";
				//std::cout << join;
				Database::getInstance().selectQuery(join.c_str());
				break;
			case 5:
				std::cout << "Enter Manager Id: ";
				std::cin >> tmp;
				query += "manager_id = '" + tmp + "';";
				Database::getInstance().selectQuery(query.c_str());
				break;
			case 6:
				all += "select * from Employee";
				Database::getInstance().selectQuery(all.c_str());
				break;
			default:
				std::cout << "Enter valid field\n";
				viewEmployee();
				break;
			}
			break;
		}
		return true;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}

}

bool Employee::insertEmployee() {
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

		s.insertSalary(getId());
		int rc = Database::getInstance().executeQuery(query.c_str());
		if (rc == 0) {
			std::cout << "Employee inserted successfully";
			return true;
		}
		else if (rc == 19) {
			std::cout << "Entered manager or department is not available in particular table\n\n";
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

bool Employee::updateEmployee() {
	try {
		std::string query = "update Employee set ";
		std::cout << "Enter the Eid to update Employee\n";
		std::string tmp;
		std::cin >> tmp;

		std::string select = "select * from Employee where id = " + tmp + " ;";
		Database::getInstance().selectQuery(select.c_str());
		if (Database::row == 0) {
			std::cout << "Entered Department is not in database\n\n";
			std::cout << "Press 0 to continue\n";
			int i;
			std::cin >> i;
			updateEmployee();
		}
		else {
			std::map<std::string, std::string> mp;
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
				i = std::stoi(input("Enter Your Choice : ", std::regex{ "^[0-9]$|^1[0-1]$" }));
				switch (i) {
				case 0:
					return true;

				case 1:
					setFirstname(input("Enter firstname: ", alphaRegex));
					mp.insert({ "firstname" , firstname });
					break;

				case 2:
					setLastname(input("Enter LastName: ", alphaRegex));
					mp.insert({ "lastname" ,  lastname });
					break;

				case 3:
					setDob(input("Enter DOB (dd-mm-yyyy): ", dateRegex));
					mp.insert({ "dob" , dob });
					break;

				case 4:
					setMobile(input("Enter Mobile: ", mobileRegex));
					mp.insert({ "mobile" , mobile });
					break;

				case 5:
					setEmail(input("Enter Email: ", emailRegex));
					mp.insert({ "email" , email });
					break;

				case 6:
					setAddress();
					mp.insert({ "address" , address });
					break;

				case 7:
					value = input("Enter Gender (Male/Female/Other: )", genderRegex);
					mp.insert({ "gender" , value });
					break;

				case 8:
					setDoj(input("Enter DOJ(dd-mm-yyyy): ", dateRegex));
					mp.insert({ "doj" , doj });
					break;

				case 9:
					setManagerId(stoi(input("Enter Manager Id: ", idRegex)));
					mp.insert({ "manager_id" , std::to_string(manager_id) });
					break;

				case 10:
					setDepartmentId(stoi(input("Enter Department Id: ", idRegex)));
					mp.insert({ "department_id" , std::to_string(department_id) });
					break;

				case 11:
					check = false;
					break;
				}
			}

			auto itr = mp.end();
			itr--;
			for (auto it = mp.begin(); it != mp.end(); ++it) {
				query += it->first + " = ";
				if (it->first == "manager_id" || it->first == "department_id") {
					query += it->second + " ";
				}
				else {
					query += "'" + it->second + "' ";
				}

				if (it != itr)
					query += ",";
			}
			query += "where Eid = " + tmp + " ;";
			//std::cout << query << "\n";

			int rc = Database::getInstance().executeQuery(query.c_str());
			return true;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

bool Employee::deleteEmployee() {
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

		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-2]" }));
		std::cout << "\n";
		std::string tmp;
		while (1) {
			switch (i) {
			case 0:
				return true;

			case 1:
				std::cout << "Enter Eid: ";
				std::cin >> tmp;
				query1 += "Eid = " + tmp + ";";
				break;

			case 2:
				std::cout << "Enter email: ";
				std::cin >> tmp;
				query1 += "email = '" + tmp + "';";

				break;

			default:
				std::cout << "Enter valid field to delete\n";
				deleteEmployee();
				break;
			}
			break;
		}
		//std::cout << query1 << "\n";

		int rc = Database::getInstance().executeQuery(query1.c_str());
		if (rc == 0) {
			int change = sqlite3_changes(Database::getInstance().db);
			if (change == 0) {
				std::cout << "Selected Employee is not in database\n";
				waitMenu();
				return false;
			}
			else {
				std::cout << "Employee Deleted successfully\n\n";
				waitMenu();
				return true;
			}
		}
		else if (rc == 19) {
			std::cout << "You can not delete this Employee because this is a manager of other employees \n\n";
			waitMenu();
			return false;
		}


	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

void Employee::action() noexcept {

}

void Employee::userInputEmployee() {
	try {

		std::string msg = " Enter # to leave the field Empty\n";
		setId(stoi(input("Enter Eid: ", idRegex)));
		setFirstname(input("Enter FirstName: " + msg, alphaRegex));
		setLastname(input("Enter LastName: " + msg, alphaRegex));
		setDob(input("Enter DOB (dd-mm-yyyy): " + msg, dateRegex));
		setMobile(input("Enter Mobile: " + msg, mobileRegex));
		setEmail(input("Enter Email: " + msg, emailRegex));
		setAddress();

		string gender = input("Enter Gender(Male / Female / Other): ", genderRegex);
		if (gender == "Male") {
			setGender(Gender::Male);
		}
		else if (gender == "Female") {
			setGender(Gender::Female);
		}
		else {
			setGender(Gender::Other);
		}

		setDoj(input("Enter DOJ(dd-mm-yyyy): " + msg, dateRegex));
		setManagerId(stoi(input("Enter Manager Id: ", idRegex)));
		setDepartmentId(stoi(input("Enter Department Id: ", idRegex)));
		s.userInputSalary();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
	}
}