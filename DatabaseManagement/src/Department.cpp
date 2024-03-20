#include "../include/Model/Department.h"

void Department::userInput() {
	try {
		system("cls");
		setId(stoi(input("Enter Department ID: ", idRegex)));
		setName();
		setManagerId(stoi(input("Enter Department Manager ID: ", idRegex)));
		setDescription();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
	}
}

bool Department::viewDepartment() {
	try {
		system("cls");
		std::string query = "select * from Department where ";
		std::string all;
		std::cout << "Select the Field on which you want to view the Department\n";
		std::cout << "0. Go Back\n";
		std::cout << "1. Id\n";
		std::cout << "2. Dname\n";
		std::cout << "3. manager_id\n";
		std::cout << "4. ALL\n\n";
		int i;
		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-4]" }));

		std::cout << "\n\n";
		std::string tmp;
		while (1) {

			switch (i) {
			case 0:
				return true;
				break;
			case 1:
				std::cout << "Enter Did: ";
				std::cin >> tmp;
				query += "id = " + tmp + ";";

				break;
			case 2:
				std::cout << "Enter Dname: ";
				std::cin >> tmp;
				query += "Dname = '" + tmp + "';";
				break;
			case 3:
				std::cout << "Enter manager Id: ";
				std::cin >> tmp;
				query += "manager_id = " + tmp + ";";
				break;
			case 4:
				all = "select * from Department ;";
				Database::getInstance().selectQuery(all.c_str());
				break;
			default:
				std::cout << "Enter valid field to delete\n";
				viewDepartment();
				break;
			}
			break;
		}
		if (i != 4) {
			int rc = Database::getInstance().selectQuery(query.c_str());
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

bool Department::insertDepartment() {
	try {
		system("cls");
		std::cout << "If you want to go back press 0 Otherwise press 1\n";
		int i;
		if (i = std::stoi(input("", std::regex{ "^[0-1]$" }));  i == 0) {
			return true;
		}

		userInput();
		std::string query = "INSERT INTO Department "
			"(id, Dname, manager_id, description) "
			"VALUES (" + std::to_string(Did) + ", '" + Dname + "'," + std::to_string(manager_id) + ", '" + description + "');";
		//std::cout << query;   
		int rc = Database::getInstance().executeQuery(query.c_str());
		if (rc == 19) {
			std::cout << "Entered manager is not available in partivular table \n\n";
			waitMenu();
			return false;
		}
		else if (rc == 0) {
			std::cout << "Department added successfully \n\n";
			waitMenu();
			return true;
		}
		//std::cin >> query;     
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

bool Department::updateDepartment() {

	try {
		system("cls");
		std::string query = "update Department set ";
		std::cout << "Enter the id to update Department\n";
		std::string tmp;
		std::cin >> tmp;

		std::string select = "select * from Department where id = " + tmp + " ;";
		Database::getInstance().selectQuery(select.c_str());
		if (Database::row == 0) {
			std::cout << "Entered Department is not in database\n\n";
			std::cout << "Press 0 to continue\n";
			int i;
			std::cin >> i;
			updateDepartment();
		}
		else {
			std::map<std::string, std::string> mp;
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
				std::string value;
				i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-4]" }));
				switch (i) {
				case 0:
					return true;

				case 1:
					setName();
					mp.erase("Dname");
					mp.insert({ "Dname" , Dname });
					break;

				case 2:
					setManagerId(std::stoi(input("Enter Manager ID Id: ", idRegex)));
					mp.erase("manager_id");
					mp.insert({ "manager_id" , std::to_string(manager_id) });
					break;

				case 3:
					setDescription();
					mp.erase("description");
					mp.insert({ "description" , description });
					break;

				case 4:
					check = false;
					break;
				}
			}

			auto itr = mp.end();
			if (mp.size() != 0) itr--;
			for (auto it = mp.begin(); it != mp.end(); ++it) {
				query += it->first + " = ";
				if (it->first == "manager_id") {
					query += it->second + " ";
				}
				else {
					query += "'" + it->second + "' ";
				}

				if (it != itr)
					query += ",";
			}
			query += "where id = " + tmp + " ;";
			//std::cout << query << "\n";

			int rc = Database::getInstance().executeQuery(query.c_str());

			if (rc == 19) {
				std::cerr << "You can not assigne value because entered manager is not in database \n\n";
				waitMenu();
				return false;
			}
			else if (rc == 0) {
				std::cout << "Department Updated successfully \n\n";
				waitMenu();
				return true;
			}
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

bool Department::deleteDepartment() {

	try {
		system("cls");
		std::string query = "delete from Department where ";
		std::cout << "Select the Field on which you want to perform delete Operation\n";
		std::cout << "0. Go Back\n";
		std::cout << "1. Did\n";
		std::cout << "2. Dname\n";
		int i;
		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-2]" }));
		std::cout << "\n";
		std::string tmp;
		while (1) {
			switch (i) {
			case 0:
				return true;

			case 1:
				std::cout << "Enter Did: ";
				std::cin >> tmp;
				query += "id = " + tmp + ";";
				//std::cout << query;  

				break;
			case 2:
				std::cout << "Enter Dname: ";
				std::cin >> tmp;
				query += "Dname = '" + tmp + "';";
				//std::cout << query;
				break;
			default:
				std::cout << "Enter valid field to delete\n";
				deleteDepartment();
				break;
			}
			break;
		}

		//int rc{};
		int rc = Database::getInstance().executeQuery(query.c_str());
		if (rc == 0) {
			int change = sqlite3_changes(Database::getInstance().db);
			if (change == 0) {
				std::cout << "Selected Department is not in database\n";
				return false;
			}
			else {

				std::cout << "Department Deleted successfully \n\n";
				return true;
			}
			waitMenu();
		}
		else if (rc == 19) {
			std::cout << "You can not Delete this department because there is employee which are working in this department  \n\n";
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

void Department::action() noexcept {
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
			viewDepartment();
			break;

		case 2:
			insertDepartment();
			break;

		case 3:
			updateDepartment();
			break;

		case 4:
			deleteDepartment();
			break;

		case 5:
			check = false;
			break;

		default:
			std::cout << "Enter Valid Choice\n";
		}
	}*/
}