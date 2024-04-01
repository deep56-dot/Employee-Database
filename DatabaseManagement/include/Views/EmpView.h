#ifndef _EmpView_
#define _EmpView_
#include"../Model/Employee.h"
#include "SalaryView.h"

inline std::optional<Model::Employee> userInputEmployee() {
	try {
		system("cls");
		Model::Employee e;
		std::string msg = " Enter # to leave the field Empty: \n";
		if (auto tmp = input("Enter Eid: ", idRegex); tmp.has_value()) e.setId(std::stoi(tmp.value()));
		else return std::nullopt;

		if (auto tmp = input("Enter FirstName OR " + msg, alphaRegex); tmp.has_value()) e.setFirstname(tmp.value());
		else return std::nullopt;

		if (auto tmp = input("Enter LastName OR " + msg, alphaRegex); tmp.has_value()) e.setLastname(tmp.value());
		else return std::nullopt;

		if (auto tmp = input("Enter DOB (dd-mm-yyyy) OR " + msg, dateRegex); tmp.has_value()) e.setDob(tmp.value());
		else return std::nullopt;

		if (auto tmp = input("Enter Mobile OR " + msg, mobileRegex); tmp.has_value()) e.setMobile(tmp.value());
		else return std::nullopt;

		if (auto tmp = input("Enter Email OR " + msg, emailRegex); tmp.has_value()) e.setEmail(tmp.value());
		else return std::nullopt;

		if (auto tmp = input("Enter Address OR " + msg, allRegex); tmp.has_value()) e.setAddress(tmp.value());
		else return std::nullopt;

		auto gender = input("Enter Gender(Male / Female / Other): ", genderRegex);
		if (gender.has_value()) {
			if (gender.value() == "Male") {
				e.setGender(Gender::Male);
			}
			else if (gender.value() == "Female") {
				e.setGender(Gender::Female);
			}
			else {
				e.setGender(Gender::Other);
			}
		}
		else {
			return std::nullopt;
		}

		if (auto tmp = input("Enter DOJ(dd-mm-yyyy) OR " + msg, dateRegex); tmp.has_value()) e.setDoj(tmp.value());
		else return std::nullopt;

		if (auto tmp = input("Enter Manager Id: ", idRegex); tmp.has_value()) e.setManagerId(stoi(tmp.value()));
		else return std::nullopt;

		if (auto tmp = input("Enter Department Id: ", idRegex); tmp.has_value()) e.setDepartmentId(stoi(tmp.value()));
		else return std::nullopt;

		if (auto tmp = userInputSalary(); tmp.has_value()) e.s = tmp.value();
		else return std::nullopt;

		return  e;

	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return std::nullopt;
	}
}
inline std::optional<Model::Employee> updateEmpViewer() {
	try {
		system("cls");

		Model::Employee e;
		e.setId(std::stoi(input("Enter the Eid to update Employee : ", idRegex).value()));

		std::string select = "select * from Employee where id = " + std::to_string(e.getId()) + ";";

		DB::Database::getInstance().selectQuery(select.c_str());

		if (DB::Database::row == 0) {
			std::cout << "\x1b[33m Employee is not in database \x1b[0m\n";
			waitMenu();
			return std::nullopt;
		}
		auto tmp = Model::Employee::getEmployee(std::to_string(e.getId()));

		if (tmp.has_value()) {

			system("cls");
			e = tmp.value();
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

				i = std::stoi(input("Enter Your Choice : ", std::regex{ "^[0-9]$|^1[0-1]$" }).value_or("0"));
				switch (i) {
				case 0:
					return std::nullopt;
					break;
				case 1:
					if (auto tmp = input("Enter FirstName: ", alphaRegex); tmp.has_value()) e.setFirstname(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return std::nullopt;
					}

					break;

				case 2:
					if (auto tmp = input("Enter LastName: ", alphaRegex); tmp.has_value()) e.setLastname(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return std::nullopt;
					}

					break;

				case 3:
					if (auto tmp = input("Enter DOB (dd-mm-yyyy): ", dateRegex); tmp.has_value()) e.setDob(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return std::nullopt;
					}

					break;

				case 4:
					if (auto tmp = input("Enter Mobile OR: ", mobileRegex); tmp.has_value()) e.setMobile(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return std::nullopt;
					}

					break;

				case 5:
					if (auto tmp = input("Enter Email: ", emailRegex); tmp.has_value()) e.setEmail(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return std::nullopt;
					}

					break;

				case 6:
					if (auto tmp = input("Enter Address: ", allRegex); tmp.has_value()) e.setAddress(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return std::nullopt;
					}

					break;

				case 7:
				{
					auto gender = input("Enter Gender(Male / Female / Other): ", genderRegex);
					if (gender.has_value()) {
						if (gender.value() == "Male") {
							e.setGender(Gender::Male);
						}
						else if (gender.value() == "Female") {
							e.setGender(Gender::Female);
						}
						else {
							e.setGender(Gender::Other);
						}
					}
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return std::nullopt;
					}

					break;
				}

				case 8:
					if (auto tmp = input("Enter DOJ(dd-mm-yyyy): ", dateRegex); tmp.has_value())  e.setDoj(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return std::nullopt;
					}

					break;

				case 9:
					if (auto tmp = input("Enter Manager Id: ", idRegex); tmp.has_value()) e.setManagerId(stoi(tmp.value()));
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return std::nullopt;
					}

					break;

				case 10:
					if (auto tmp = input("Enter Department Id: ", idRegex); tmp.has_value()) e.setDepartmentId(stoi(tmp.value()));
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return std::nullopt;
					}

					break;

				case 11:
					check = false;
					break;
				}
			}
			return e;
		}
		else {
			std::cout << "\x1b[33m Employee is not in database!!! \x1b[0m\n";
			return std::nullopt;
		}
	}
	catch (std::exception& e) {
		return std::nullopt;
	}
}
inline std::optional<std::pair<string, string>> viewEmp() {
	try {
		system("cls");
		std::pair<std::string, std::string> p;
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
		while (1) {
			switch (i) {
			case 0:
				return std::nullopt;
				break;
			case 1:
				if (auto tmp = input("Enter Eid: ", idRegex); tmp.has_value()) {
					p = std::make_pair("Eid", tmp.value());
				}
				else {
					return std::nullopt;
				}
				break;
			case 2:
				if (auto tmp = input("Enter Fname: ", alphaRegex); tmp.has_value()) {
					p = std::make_pair("firstname", tmp.value());
				}
				else {
					return std::nullopt;
				}
				break;
			case 3:
				if (auto tmp = input("Enter Email: ", emailRegex); tmp.has_value()) {
					p = std::make_pair("email", tmp.value());
				}
				else {
					return std::nullopt;
				}
				break;
			case 4:
				if (auto tmp = input("Enter Dname: ", allRegex); tmp.has_value()) {
					p = std::make_pair("Dname", tmp.value());
				}
				else {
					return std::nullopt;
				}
				break;
			case 5:
				if (auto tmp = input("Enter Manager Id: ", idRegex); tmp.has_value()) {
					p = std::make_pair("manager_id", tmp.value());
				}
				else {
					return std::nullopt;
				}
				break;
			case 6:
				p = std::make_pair("all", "all");
				break;

			default:
				std::cout << "Enter valid field\n";
				viewEmp();
				break;
			}
			break;
		}
		return p;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return std::nullopt;
	}

}
inline std::optional<Model::Employee> deleteEmpViewer() {
	try {
		system("cls");

		Model::Employee d;
		std::cout << "Select the Field on which you want to perform delete Operation\n";
		std::cout << "0. Go Back\n";
		std::cout << "1. Eid\n";
		int i;
		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-1]" }).value_or("0"));
		std::cout << "\n";
		while (1) {
			switch (i) {
			case 0:
				return std::nullopt;

			case 1:
				if (auto tmp = input("Enter Employee ID: ", idRegex); tmp.has_value()) d.setId(std::stoi(tmp.value()));
				else {
					;
					return std::nullopt;
				}
				break;
			default:
				std::cout << "Enter valid field to delete\n";
				deleteEmpViewer();
				break;
			}
			break;
		}
		return d;
	}
	catch (std::exception e) {
		return std::nullopt;
	}
}
#endif
