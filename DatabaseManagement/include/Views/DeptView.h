#pragma once
#include "../Model/Department.h"
#include<optional>
#include<utility>

inline std::optional<Model::Department> userinputDepartment() {
	try {
		system("cls");
		std::cout << "If you want to go back press 0 Otherwise press 1\n";
		int i;
		if (i = std::stoi(input("", std::regex{ "^[0-1]$" }).value_or("0"));  i == 0) {
			return std::nullopt;
		}
		Model::Department d;
		std::string msg = " Enter # to leave the field Empty: \n";
		if (auto tmp = input("Enter Department ID: ", idRegex); tmp.has_value()) d.setId(std::stoi(tmp.value()));
		else return std::nullopt;

		if (auto tmp = input("Enter Department Name OR " + msg, allRegex); tmp.has_value()) d.setName(tmp.value());
		else return std::nullopt;

		if (auto tmp = input("Enter Manager ID: ", idRegex); tmp.has_value()) d.setManagerId(std::stoi(tmp.value()));
		else return std::nullopt;

		if (auto tmp = input("Enter Description OR " + msg, allRegex); tmp.has_value()) d.setDescription(tmp.value());
		else return std::nullopt;

		return d;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return std::nullopt;
	}
}

inline std::optional<std::pair<std::string, std::string>> viewDept() {
	try {

		std::pair<std::string, std::string> p;

		system("cls");
		//std::string query = "select * from Department where "; 
		std::string all;
		std::cout << "Select the Field on which you want to view the Department\n";
		std::cout << "0. Go Back\n";
		std::cout << "1. Id\n";
		std::cout << "2. Dname\n";
		std::cout << "3. manager_id\n";
		std::cout << "4. ALL\n\n";
		int i;
		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-4]" }).value_or("0"));

		std::cout << "\n\n";
		while (1) {

			switch (i) {
			case 0:
				return std::nullopt;

				break;
			case 1:
				if (auto tmp = input("Enter Did: ", idRegex); tmp.has_value()) {
					p = std::make_pair("id", tmp.value());
				}
				else {
					return std::nullopt;
				}
				break;

			case 2:
				if (auto tmp = input("Enter Dname: ", allRegex); tmp.has_value()) {
					p = std::make_pair("Dname", tmp.value());
				}
				else {
					return std::nullopt;
				}
				break;

			case 3:
				if (auto tmp = input("Enter manager Id: ", idRegex); tmp.has_value()) {
					p = std::make_pair("manager_id", tmp.value());
				}
				else {
					return std::nullopt;
				}
				//query += "manager_id = " + tmp + ";"; 
				break;

			case 4:
				p = std::make_pair("all", "all");
				break;

			default:
				std::cout << "Enter valid field to delete\n";
				viewDept();
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

inline std::optional<Model::Department> updateDeptViewer() {
	try {
		system("cls");
		Model::Department d;
		d.setId(std::stoi(input("Enter the Did to update Department : ", idRegex).value()));
		std::string select = "select * from Department where id = " + std::to_string(d.getId()) + ";";

		DB::Database::getInstance().selectQuery(select.c_str());

		if (DB::Database::row == 0) {
			std::cout << "\x1b[33m Department is not in database \x1b[0m\n";
			waitMenu();
			return std::nullopt;
		}

		auto tmp = Model::Department::getDepartment(std::to_string(d.getId()));

		if (tmp.has_value()) {

			system("cls");
			d = tmp.value();
			bool check = true;
			int i;
			while (check) {
				system("cls");
				std::cout << "Select the field you want to update \n";
				std::cout << "0. Go Back\n";
				std::cout << "1. Department name\n";
				std::cout << "2. manager id\n";
				std::cout << "3. description\n";
				std::cout << "4. toUpdateDatabase\n\n";
				i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-4]" }).value_or("0"));
				switch (i) {
				case 0:
					return std::nullopt;

				case 1:
					if (auto tmp = input("Enter Department Name: ", allRegex); tmp.has_value()) d.setName(tmp.value());
					else {
						return std::nullopt;
					}
					break;

				case 2:
					if (auto tmp = input("Enter Department Manager ID: ", idRegex); tmp.has_value()) d.setManagerId(std::stoi(tmp.value()));
					else {
						return std::nullopt;
					}
					break;

				case 3:
					if (auto tmp = input("Enter Description :  ", allRegex); tmp.has_value()) d.setDescription(tmp.value());
					else {
						return std::nullopt;
					}
					break;

				case 4:
					check = false;
					break;
				}
			}
			return d;
		}
		else {
			std::cout << "\x1b[33m Departement is not in database!!! \x1b[0m\n";
			return std::nullopt;
		}
	}
	catch (const std::exception& e) {
		return std::nullopt;
	}
}

inline std::optional<Model::Department> deleteDeptViewer() {
	try {
		system("cls");

		Model::Department d;
		std::cout << "Select the Field on which you want to perform delete Operation\n";
		std::cout << "0. Go Back\n";
		std::cout << "1. Did\n";
		int i;
		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-1]" }).value_or("0"));
		std::cout << "\n";
		while (1) {
			switch (i) {
			case 0:
				return std::nullopt;

			case 1:
				if (auto tmp = input("Enter Department ID: ", idRegex); tmp.has_value()) d.setId(std::stoi(tmp.value()));
				else {
					;
					return std::nullopt;
				}
				break;
			default:
				std::cout << "Enter valid field to delete\n";
				deleteDeptViewer();
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