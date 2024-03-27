#include <iostream>
#include "sqlite/sqlite3.h"
#include "include/DBmanage.h"
#include "include/Helper.h"
#include "include/Model/Table.h"

void menu();

int main() {
	DB::Database::getInstance().open("Emp.db");
	auto ch{ true };
	Model::Table t;
	while (ch) {
		system("cls");
		std::cout << "------------------------------------> WELCOME TO EMPLOYEE MANAGEMENT SYSTEM <-------------------------------------------\n";
		std::cout << "Enter the Opertaion you want to perform\n";
		std::cout << "1. Create Tables\n";
		std::cout << "2. Show Tables\n";
		std::cout << "3. Delete Tables\n";
		std::cout << "4. Access Table\n";
		std::cout << "5. Access Other Tables\n";
		std::cout << "6. Backup Table\n";
		std::cout << "7. Exit\n\n";

		int i;
		i = std::stoi(input("Enter Choice: ", std::regex{ "[1-7]" }));
		switch (i) {
		case 1:
			t.createTable();
			break;

		case 2:
			t.showTables();
			break;

		case 3:
			t.deleteTable();
			break;

		case 4:
			menu();
			break;

		case 5:
			t.action();
			break;

		case 6:
			t.writeCSV();
			break;

		case 7:
			ch = false;
			break;

		default:
			std::cout << "Enter valid input: \n";
		}
	}

	
}