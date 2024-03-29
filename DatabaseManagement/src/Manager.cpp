#include "../include/Model/Manager.h"

bool Model::Manager::userInputManager() {

	try {
		std::string msg = " Enter # to leave the field Empty: \n";
		system("cls");
		if (!userInputEmployee()) return false;

		if (auto tmp = input("Enter Management Experience OR " + msg, digitRegex); tmp.has_value()) setManagementExperience(std::stoi(tmp.value()));
		else return false;

		if (auto tmp = input("Enter Project Title OR " + msg, allRegex); tmp.has_value()) setProjectTile(tmp.value());
		else return false;
		return true;
	}
	catch (std::exception& e) {
		//std::cout << e.what() << std::endl;
		//waitMenu();
		return false;
	}
}

bool Model::Manager::viewManager() {

	try {
		system("cls");
		std::string query1 = "SELECT * FROM Employee INNER JOIN Manager ON Manager.id = Employee.Eid and ";
		std::string all = "";
		std::string join = "";
		std::cout << "Select the Field on which you want to view the Manager\n";
		std::cout << "0. Go Back\n";
		std::cout << "1. Mid\n";
		std::cout << "2. fname\n";
		std::cout << "3. email\n";
		std::cout << "4. department name\n";
		std::cout << "5. Project Title\n";
		std::cout << "6. ALL\n\n";
		int i;
		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-6]" }).value_or("0"));
		std::string tmp1;
		while (1) {
			switch (i) {
			case 0:
				return true;

			case 1:
				std::cout << "Enter Mid: ";
				cin >> tmp1;
				query1 += "Employee.Eid = " + tmp1 + ";";

				break;
			case 2:
				std::cout << "Enter fname: ";
				cin >> tmp1;
				query1 += "Employee.firstname = '" + tmp1 + "';";
				break;
			case 3:
				std::cout << "Enter email: ";
				cin >> tmp1;
				query1 += "Employee.email = '" + tmp1 + "';";
				break;
			case 4:
				std::cout << "Enter departmaent name: ";
				cin >> tmp1;
				join += "SELECT e.*, m.* FROM Employee e INNER JOIN Manager m ON e.Eid = m.id INNER JOIN Department dept ON e.department_id = dept.id WHERE dept.Dname = '" + tmp1 + "' ;";
				//std::cout << join;
				DB::Database::getInstance().selectQuery(join.c_str());
				break;
			case 5:
				std::cout << "Enter Project title: ";
				cin >> tmp1;
				query1 += "Employee.project_title = '" + tmp1 + "';";
				break;
			case 6:
				all += "SELECT * FROM Employee INNER JOIN Manager ON Manager.id = Employee.Eid";
				DB::Database::getInstance().selectQuery(all.c_str());
				break;
			default:
				std::cout << "Enter valid field\n";
				viewManager();
				break;
			}
			break;
		}
		if (i != 4 && i != 6) {
			int rc = DB::Database::getInstance().selectQuery(query1.c_str());
		}
		if (DB::Database::row == 0) {
			std::cout << "\x1b[33m Selected Manager is not available!!! \x1b[0m\n";
			waitMenu();
			return false;
		}
		waitMenu();
		return true;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

bool Model::Manager::insertManager() {
	try {
		system("cls");
		std::cout << "If you want to go back press 0 Otherwise press 1\n";
		int i;
		if (i = std::stoi(input("", std::regex{ "^[0-1]$" }).value_or("0"));  i == 0) {
			return true;
		}

		bool flag = userInputManager();

		if (!flag) {
			std::cout << "\x1b[33m Insertion Failed!!! \x1b[0m\n";
			waitMenu();
			return false;
		}

		if (auto ch = insertEmployee(); ch) {
			std::string query = "";
			query += "INSERT INTO Manager VALUES ( " + to_string(getId()) + ", " + std::to_string(getManagementExperience()) + " , ' " + getProjectTitle() + " ') ;";
			//std::cout << query << "\n";
			int rc = DB::Database::getInstance().executeQuery(query.c_str());
			if (rc == 0) {
				std::cout << "\x1b[32mManager inserted successfully\x1b[0m\n\n";
				waitMenu();
				logging::Info("Engineer Added for Id: ", std::to_string(getId()));
				return true;
			}
			else if (rc == 19) {
				std::cout << "\x1b[33mEntered Manager is already exist\x1b[0m\n\n";
				waitMenu();
				return false;
			}
			return false;
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
	return false;
}

bool Model::Manager::updateManager() {

	try {
		system("cls");
		std::string query1 = "update Employee set ";
		std::string query2 = "update Manager set ";
		setId(std::stoi(input("Enter the Mid to update Manager : ", idRegex).value()));

		std::string select = "select * from Manager where id = " + std::to_string(getId()) + " ;";
		DB::Database::getInstance().selectQuery(select.c_str());
		if (DB::Database::row == 0) {
			std::cout << "Entered Manager is not in database\n\n";
			waitMenu();
			return false;
		}
		else {
			std::unordered_map<std::string, std::string> mp1;
			std::unordered_map<std::string, std::string> mp2;
			bool check = true;
			int i;
			while (check) {
				system("cls");
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
				std::cout << "11. Project Title\n";
				std::cout << "12. managetment Experience \n";
				std::cout << "13. ToUpdateDatabase\n\n";
				std::string value;
				i = std::stoi(input("Enter Your Choice : ", std::regex{ "^[0-9]$|^1[0-3]$" }).value_or("0"));
				switch (i) {
				case 0:
					return true;

				case 1:

					if (auto tmp = input("Enter FirstName: ", alphaRegex); tmp.has_value()) setFirstname(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return false;
					}
					mp1.erase("firstname");
					mp1.insert({ "firstname" , getFirstname() });
					break;

				case 2:
					if (auto tmp = input("Enter LastName: ", alphaRegex); tmp.has_value()) setLastname(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return false;
					}
					mp1.erase("lastname");
					mp1.insert({ "lastname" ,  getLastname() });
					break;

				case 3:
					if (auto tmp = input("Enter DOB (dd-mm-yyyy): ", dateRegex); tmp.has_value()) setDob(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return false;
					}
					mp1.erase("dob");
					mp1.insert({ "dob" , getDob() });
					break;

				case 4:
					if (auto tmp = input("Enter Mobile OR: ", mobileRegex); tmp.has_value()) setMobile(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return false;
					}
					mp1.erase("mobile");
					mp1.insert({ "mobile" , getMobile() });
					break;

				case 5:
					if (auto tmp = input("Enter Email: ", emailRegex); tmp.has_value()) setEmail(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return false;
					}
					mp1.erase("email");
					mp1.insert({ "email" , getEmail() });
					break;

				case 6:
					if (auto tmp = input("Enter Address: ", allRegex); tmp.has_value()) setAddress(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return false;
					}
					mp1.erase("address");
					mp1.insert({ "address" , getAddress() });
					break;

				case 7:
				{
					auto gender = input("Enter Gender(Male / Female / Other): ", genderRegex);
					if (gender.has_value()) {
						if (gender.value() == "Male") {
							setGender(Gender::Male);
						}
						else if (gender.value() == "Female") {
							setGender(Gender::Female);
						}
						else {
							setGender(Gender::Other);
						}
					}
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return false;
					}
					mp1.erase("gender");
					mp1.insert({ "gender" , gender.value() });
					break;
				}

				case 8:
					if (auto tmp = input("Enter DOJ(dd-mm-yyyy): ", dateRegex); tmp.has_value())  setDoj(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return false;
					}
					mp1.erase("doj");
					mp1.insert({ "doj" , getDoj() });
					break;

				case 9:
					if (auto tmp = input("Enter Manager Id: ", idRegex); tmp.has_value()) setManagerId(stoi(tmp.value()));
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return false;
					}
					mp1.erase("manager_id");
					mp1.insert({ "manager_id" , std::to_string(getManagerId()) });
					break;

				case 10:
					if (auto tmp = input("Enter Department Id: ", idRegex); tmp.has_value()) setDepartmentId(stoi(tmp.value()));
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return false;
					}
					mp1.erase("department_id");
					mp1.insert({ "department_id" , std::to_string(getDepartmentId()) });
					break;

				case 11:
					if (auto tmp = input("Enter Project Title: ", allRegex); tmp.has_value()) setProjectTile(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return false;
					}
					mp2.erase("project_title");
					mp2.insert({ "project_title" , project_title });
					break;

				case 12:
					if (auto tmp = input("Enter Management Experience: ", digitRegex); tmp.has_value()) setManagementExperience(std::stoi(tmp.value()));
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return false;
					}
					mp2.erase("management_experience");
					mp2.insert({ "management_experience" , std::to_string(getManagementExperience()) });
					break;

				case 13:
					check = false;
					break;
				}
			}

			auto itr1 = mp1.end();
			auto itr2 = mp2.end();
			if (mp1.size() != 0) itr1--;
			if (mp2.size() != 0) itr2--;
			for (auto it = mp1.begin(); it != mp1.end(); ++it) {

				auto& [field, value] = *it;

				query1 += field + " = ";
				if (field == "manager_id" || field == "department_id") {
					query1 += value + " ";
				}
				else {
					query1 += "'" + value + "' ";
				}
				if (it != itr1)
					query1 += ",";
			}

			for (auto it = mp2.begin(); it != mp2.end(); ++it) {

				auto& [field, value] = *it;

				query2 += field + " = ";
				if (field == "management_experience") {
					query2 += value + " ";
				}
				else {
					query2 += "'" + value + "' ";
				}
				if (it != itr2)
					query2 += ",";
			}

			query1 += " where Eid = " + std::to_string(getId()) + " ;";
			query2 += " where id = " + std::to_string(getId()) + " ;";
			//std::cout << query1 << "\n"; 
			//std::cout << query2 << "\n"; 

			int rc{};
			if (mp1.size() != 0) {

				rc = DB::Database::getInstance().executeQuery(query1.c_str());
			}

			if (mp2.size() != 0) {

				rc = DB::Database::getInstance().executeQuery(query2.c_str());
			}

			if (rc == 0) {
				std::cout << "\x1b[32mManager updated successfully\x1b[0m\n\n";
				waitMenu();
				logging::Info("Manager updated for Id: ", std::to_string(getId()));
				return true;
			}
			else if (rc == 19) {
				std::cout << "\x1b[33mYou can not update that value Because entered manager or department is not in particular table\x1b[0m\n\n";
				waitMenu();
				return false;
			}
		}
		return false;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
		waitMenu();
		return false;
	}
	return false;
}

bool Model::Manager::deleteManager() {

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

void Model::Manager::action() noexcept {
	/*auto check{ true };
	while (check) {
		system("cls");
		std::cout << "Select The Operation You Want The Perform\n";
		std::cout << "1. View\n";
		std::cout << "2. Insert\n";
		std::cout << "3. Update\n";
		std::cout << "4. Delete\n";
		std::cout << "5. Go to Main Menu\n\n";

		std::cout << "Enter Choice : ";
		int i;
		std::cin >> i;
		switch (i) {
		case 1:
			viewManager();
			break;

		case 2:
			insertManager();
			break;

		case 3:
			updateManager();
			break;

		case 4:
			deleteManager();
			break;

		case 5:
			check = false;
			break;

		default:
			std::cout << "Enter Valid Choice\n";
		}
	}*/
}