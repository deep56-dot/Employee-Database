#include "../include/Model/Department.h"
#include "../include/Model/Engineer.h" 
#include "../include/Model/Manager.h"
#include "../include/Model/Table.h"
#include "../include/Views/EmpView.h"
#include "../include/Views/EngView.h"
#include "../include/Views/MangView.h"
#include "../include/Views/DeptView.h"
#include "../include/Views/SalaryView.h"



#include<optional>
using namespace std;

void salaryAction() {

	auto check{ true };

	while (check) {
		system("cls");
		std::cout << "Select The Operation You Want The Perform\n";
		std::cout << "1. View\n";
		std::cout << "2. Update\n";
		std::cout << "3. Go to Main Menu\n\n";

		Model::Salary s;

		int i;
		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[1-3]" }).value_or("3"));
		switch (i) {
		case 1:
			s.viewSalary();
			break;

		case 2:
		{
			auto s1 = updateSalaryViewer();
			if (s1.has_value())
				s1.value().updateSalary();
			else {
				std::cerr << "\x1b[33m Updation Failed \x1b[0m\n\n";
				waitMenu();
			}
			break;
		}


		case 3:
			check = false;
			break;

		default:
			std::cout << "Enter Valid Choice\n";

		}
	}
}

void tableAction() {
	auto tables = Model::Table::getAllTables();
	system("cls");
	for (auto& table : tables) {
		std::cout << "-> " << table.getname() << "\n";
	}

	std::string tableName = input("Enter the name of the table you want to access from above tables: ", alphaRegex).value();
	auto t = Model::Table::getTable(tableName);
	if (t.has_value()) {
		auto ch{ true };
		while (ch) {
			system("cls");
			std::cout << "Enter the opearation you want to perform: \n";
			std::cout << "1. View Record\n";
			std::cout << "2. View All Record\n";
			std::cout << "3. Insert Record\n";
			std::cout << "4. Update Record\n";
			std::cout << "5. Delete Record\n";
			std::cout << "6. Show Schema\n";
			std::cout << "7. Go Back\n";

			int i = std::stoi(input("Enter Choice: ", std::regex{ "^[1-7]$" }).value_or("7"));
			switch (i) {
			case 1:
				t.value().viewRecord();
				break;

			case 2:
				t.value().viewAllRecords();
				break;

			case 3:
				t.value().insertRecord();
				break;

			case 4:
				t.value().updateRecord();
				break;

			case 5:
				t.value().deleteRecord();
				break;

			case 6:
				t.value().infoTable();
				break;

			case 7:
				ch = false;
				break;
			}
		}
	}
	else {
		system("cls");
		std::cout << "\x1b[33mEntered table is not exist in database\x1b[0m\n";
		waitMenu();
	}
}

void action(int j) noexcept {
	auto check{ true };
	while (check) {
		system("cls");
		std::cout << "Select The Operation You Want The Perform\n";
		std::cout << "1. View\n";
		std::cout << "2. Insert\n";
		std::cout << "3. Update\n";
		std::cout << "4. Delete\n";
		std::cout << "5. Go to Main Menu\n\n";

		int i;
		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[1-5]" }).value_or("5"));
		Model::Engineer e;
		Model::Manager m;
		Model::Department d;
		switch (j) {
		case 1:
			switch (i) {
			case 1:
				e.viewEngineer();
				break;

			case 2:
			{
				auto e1 = userInputEngineer();
				if (e1.has_value()) {
					e1.value().insertEngineer();
				}
				else {
					std::cerr << "\x1b[33m Insertion Failed \x1b[0m\n\n";
					waitMenu();
				}
				break;
			}

			case 3:
			{
				auto e1 = updateEngViewer();
				if (e1.has_value()) {
					e1.value().updateEngineer();
				}
				else {
					std::cerr << "\x1b[33m Updation Failed \x1b[0m\n\n";
					waitMenu();
				}
				break;
			}

			case 4:
			{
				auto e1 = deleteEmpViewer();
				if (e1.has_value()) {
					e1.value().deleteEmployee();
				}
				else {
					std::cerr << "\x1b[33m Insertion Failed \x1b[0m\n\n";
					waitMenu();
				}
				break;
			}

			case 5:
				check = false;
				break;
			}
			break;

		case 2:
			switch (i) {
			case 1:
				m.viewManager();
				break;

			case 2:
			{
				auto e1 = userInputManager();
				if (e1.has_value()) {
					e1.value().insertManager();
				}
				else {
					std::cerr << "\x1b[33m Insertion Failed \x1b[0m\n\n";
					waitMenu();
				}
				break;
			}

			case 3:
			{
				auto e1 = updateMangViewer();
				if (e1.has_value()) {
					e1.value().updateManager();
				}
				else {
					std::cerr << "\x1b[33m Updation Failed \x1b[0m\n\n";
					waitMenu();
				}
				break;
			}

			case 4:
			{
				auto e1 = deleteEmpViewer();
				if (e1.has_value()) {
					e1.value().deleteEmployee();
				}
				else {
					std::cerr << "\x1b[33m Deletion Failed \x1b[0m\n\n";
					waitMenu();
				}
				break;
			}

			case 5:
				check = false;
				break;
			}
			break;

		case 3:
			switch (i) {
			case 1:
				d.viewDepartment();
				break;

			case 2:
			{
				auto d1 = userinputDepartment();
				if (d1.has_value())
					d1.value().insertDepartment();
				else {
					std::cerr << "\x1b[33m Insertion Failed \x1b[0m\n\n";
					waitMenu();
				}
				break;
			}

			case 3:
			{
				auto d1 = updateDeptViewer();
				if (d1.has_value())
					d1.value().updateDepartment();
				else {
					std::cerr << "\x1b[33m Updation Failed \x1b[0m\n\n";
					waitMenu();
				}
				break;
			}

			case 4:
			{
				auto d1 = deleteDeptViewer();
				if (d1.has_value())
					d1.value().deleteDepartment();
				else {
					std::cerr << "\x1b[33m Deletion Failed \x1b[0m\n\n";
					waitMenu();
				}
				break;
			}

			case 5:
				check = false;
				break;
			}
			break;

		default:
			std::cout << "Enter Valid Choice\n";
		}
	}
}