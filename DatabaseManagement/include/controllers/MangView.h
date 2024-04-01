#pragma once

#include "../Model/Manager.h"

std::optional<std::pair<string, string>> viewEmp();
std::optional<Model::Salary> userInputSalary();

inline std::optional<Model::Manager> userInputManager() {
	try {
		system("cls");
		Model::Manager e;
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

		if (auto tmp = input("Enter Management Experience OR " + msg, digitRegex); tmp.has_value()) e.setManagementExperience(std::stoi(tmp.value()));
		else return std::nullopt;

		if (auto tmp = input("Enter Project Title OR ", allRegex); tmp.has_value()) e.setProjectTile(tmp.value());
		else return std::nullopt;

		return  e;

	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return std::nullopt;
	}
}

inline std::optional<std::pair<std::string, std::string>> viewMang() {
	system("cls");
	return viewEmp();
}

inline std::optional<Model::Manager> updateMangViewer() {
	try {
		system("cls");

		Model::Manager e;
		e.setId(std::stoi(input("Enter the Eid to update Manager : ", idRegex).value()));

		std::string select = "select * from Manager where id = " + std::to_string(e.getId()) + ";";

		DB::Database::getInstance().selectQuery(select.c_str());

		if (DB::Database::row == 0) {
			std::cout << "\x1b[33m Manager is not in database \x1b[0m\n";
			waitMenu();
			return std::nullopt;
		}

		auto tmp = Model::Manager::getManager(std::to_string(e.getId()));

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
				std::cout << "11. Management Experience\n";
				std::cout << "12. Project Title\n";
				std::cout << "13. toUpdateDatabase\n";

				i = std::stoi(input("Enter Your Choice : ", std::regex{ "^[0-9]$|^1[0-3]$" }).value_or("0"));
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
					if (auto tmp = input("Enter Management Experience: ", allRegex); tmp.has_value()) e.setManagementExperience(std::stoi(tmp.value()));
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return std::nullopt;
					}
					break;

				case 12:
					if (auto tmp = input("Enter Project Title: ", allRegex); tmp.has_value()) e.setProjectTile(tmp.value());
					else {
						std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
						waitMenu();
						return std::nullopt;
					}
					break;

				case 13:
					check = false;
					break;
				}
			}
			return e;
		}
		else {
			std::cout << "\x1b[33m Manager is not in database!!! \x1b[0m\n";
			return std::nullopt;
		}
	}
	catch (std::exception& e) {
		return std::nullopt;
	}
}