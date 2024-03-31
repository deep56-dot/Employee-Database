//#include "SalaryView.h"
//inline std::optional<Model::Salary> userInputSalary() {
//
//	try {
//		Model::Salary s;
//		std::string msg = " Enter # to leave the field Empty: \n";
//
//		if (auto tmp = input("Enter Base Salary OR " + msg, salaryRegex, true); tmp.has_value()) s.setBaseSalary(std::stof(tmp.value()));
//		else return std::nullopt;
//
//		if (auto tmp = input("Enter Bonus OR " + msg, salaryRegex, true); tmp.has_value()) s.setBonus(std::stof(tmp.value()));
//		else return std::nullopt;
//
//		s.setAmount(s.getBaseSalary() + s.getBonus());
//		return s;
//	}
//	catch (std::exception& e) {
//		std::cout << e.what() << std::endl;
//		waitMenu();
//		return std::nullopt;
//	}
//}
//inline std::optional<Model::Salary> updateSalaryViewer() {
//	try {
//		system("cls");
//
//		Model::Salary e;
//		e.setId(std::stoi(input("Enter the Sid to update Salary : ", idRegex).value()));
//
//		auto tmp = Model::Salary::getSalary(std::to_string(e.getId()));
//
//		if (tmp.has_value()) {
//
//			e = tmp.value();
//			bool check = true;
//			int i;
//			while (check) {
//				system("cls");
//				std::cout << "Select the field you want to update \n";
//				std::cout << "0. Go Back\n";
//				std::cout << "1. Base Salary\n";
//				std::cout << "2. Bonus\n";
//				std::cout << "3. Increment\n";
//				std::cout << "4. ToUpdate\n";
//
//				std::string value;
//				i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-4]" }).value_or("0"));
//				switch (i) {
//				case 0:
//					return std::nullopt;
//					break;
//				case 1:
//					if (auto tmp = input("Enter Base Salary: ", salaryRegex, true); tmp.has_value()) e.setBaseSalary(std::stof(tmp.value()));
//					else {
//						std::cout << "\x1b[33m Updation Fail!!! \x1b[0m\n";
//						waitMenu();
//						return std::nullopt;
//					}
//					break;
//
//				case 2:
//					if (auto tmp = input("Enter Bonus: ", salaryRegex, true); tmp.has_value()) e.setBonus(std::stof(tmp.value()));
//					else {
//						std::cout << "\x1b[33m Updation Fail!!! \x1b[0m\n";
//						waitMenu();
//						return std::nullopt;
//					}
//					break;
//
//				case 3:
//					if (auto tmp = input("Enter Precentage By which you want to : ", salaryRegex, true); tmp.has_value()) e.increment(std::stof(tmp.value()), e.getId());
//					else {
//						std::cout << "\x1b[33m Updation Fail!!! \x1b[0m\n";
//						waitMenu();
//						return std::nullopt;
//					}
//
//					break;
//
//				case 4:
//					check = false;
//					break;
//				}
//			}
//			return e;
//		}
//		else {
//			std::cout << "\x1b[33m Employee is not in database!!! \x1b[0m\n";
//			return std::nullopt;
//		}
//	}
//	catch (std::exception& e) {
//		return std::nullopt;
//	}
//}
//inline std::optional<std::pair<std::string, std::string>> SalaryViewer() {
//	try {
//
//		std::pair<std::string, std::string> p;
//
//		system("cls");
//
//		std::cout << "Select the Field on which you want to view the Salary\n";
//		std::cout << "0. Go Back\n";
//		std::cout << "1. Id\n";
//		std::cout << "2. ALL\n\n";
//		int i;
//		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-4]" }).value_or("0"));
//
//		std::cout << "\n\n";
//		while (1) {
//
//			switch (i) {
//			case 0:
//				return std::nullopt;
//
//				break;
//			case 1:
//				if (auto tmp = input("Enter Eid: ", idRegex); tmp.has_value()) {
//					p = std::make_pair("id", tmp.value());
//				}
//				else {
//					return std::nullopt;
//				}
//				break;
//
//			case 2:
//				p = std::make_pair("all", "all");
//				break;
//
//			default:
//				std::cout << "Enter valid field to delete\n";
//				SalaryViewer();
//				break;
//			}
//			break;
//		}
//
//		return p;
//	}
//	catch (std::exception& e) {
//		std::cout << e.what() << std::endl;
//		waitMenu();
//		return std::nullopt;
//	}
//}