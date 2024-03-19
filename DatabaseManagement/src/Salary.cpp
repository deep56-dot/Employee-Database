#include "../include/Model/Salary.h"
#include "../include/Regex.h"
void Salary::userInputSalary() {

	try {
		std::string msg = " Enter # to leave the field Empty\n";
		setBaseSalary(std::stof(input("Enter Base Salary: ", salaryRegex)));
		setBonus(std::stof(input("Enter Bonus: ", salaryRegex)));
		setAmount(base_salary + bonus);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
	}
}

void Salary::increment(double percentage, std::string id) {
	try {
		double val = 0;
		std::string query = "select amount from Salary where Sid = " + id + " ;";
		int rc = sqlite3_prepare_v2(Database::getInstance().db, query.c_str(), -1, &Database::getInstance().stmt, nullptr);
		rc = sqlite3_step(Database::getInstance().stmt);
		if (rc == SQLITE_ROW) {
			// Get the value of the 'amount' column
			val = sqlite3_column_double(Database::getInstance().stmt, 0);
			//std::cout << "Amount: " << val << std::endl;
		}
		else {
			//std::cerr << "No rows returned" << std::endl;
		}

		val = (val + ((val * percentage) / 100));
		amount = val;
		setAmount(val);

		//std::cout << amount << "\n";
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
	}
}

void Salary::viewSalary() {
	try {
		system("cls");
		std::string query = "select Employee.Eid , Employee.firstname , Employee.lastname , Employee.email , Salary.amount , Salary.base_salary , Salary.bonus from Employee JOIN Salary ON Employee.Eid = Salary.Sid where Sid =  ";
		std::string tmp;
		std::cout << "Enter Eid to view salary :";
		std::cin >> tmp;
		query += tmp + " ;";
		Database::getInstance().selectQuery(query.c_str());
		waitMenu();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
	}
}

void Salary::insertSalary(int id) const {
	try {
		std::string query = "insert into Salary values(" + std::to_string(id) + " , " + std::to_string(getAmount()) + " , " + std::to_string(getBaseSalary()) + " ," + std::to_string(getBonus()) + ") ;";
		std::cout << query;
		Database::getInstance().executeQuery(query.c_str());
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
	}
}

void Salary::updateSalary() {
	try {
		system("cls");
		std::string query = "update Salary set ";
		std::cout << "Enter the Eid to update Salary : ";
		std::string tmp;
		std::cin >> tmp;

		std::string select = "select * from Salary where Sid = " + tmp + " ;";
		Database::getInstance().selectQuery(select.c_str());
		if (Database::row == 0) {
			std::cout << "Entered Employee is not in database\n\n";
			std::cout << "Press 0 to continue\n";
			int i;
			std::cin >> i;
			updateSalary();
		}
		else {
			std::string query1 = "select base_salary from Salary where Sid = " + tmp + " ;";
			int rc = sqlite3_prepare_v2(Database::getInstance().db, query1.c_str(), -1, &Database::getInstance().stmt, nullptr);
			rc = sqlite3_step(Database::getInstance().stmt);
			base_salary = sqlite3_column_double(Database::getInstance().stmt, 0);

			query1 = "select bonus from Salary where Sid = " + tmp + " ;";
			rc = sqlite3_prepare_v2(Database::getInstance().db, query1.c_str(), -1, &Database::getInstance().stmt, nullptr);
			rc = sqlite3_step(Database::getInstance().stmt);
			bonus = sqlite3_column_double(Database::getInstance().stmt, 0);


			std::map<std::string, std::string> mp1;
			bool check = true;
			int i;
			while (check) {
				system("cls");
				std::cout << "Select the field you want to update \n";
				std::cout << "0. Go Back\n";
				std::cout << "1. Base Salary\n";
				std::cout << "2. Bonus\n";
				std::cout << "3. Increment\n";
				std::cout << "4. ToUpdate\n";

				std::string value;
				i = std::stoi(input("Enter Your Choice : ", std::regex{ "[0-4]" }));
				switch (i) {
				case 0:
					return;

				case 1:
					value = input("Enter Base Salary: ", salaryRegex);
					setBaseSalary(std::stof(value));
					mp1.erase("base_salary");
					mp1.insert({ "base_salary" , value });
					break;

				case 2:
					value = input("Enter Bonus: ", salaryRegex);
					setBonus(std::stof(value));
					mp1.erase("bonus");
					mp1.insert({ "bonus" , value });
					break;

				case 3:
					value = input("Enter Percantage by which you want to increase the salary :");
					setAmount(base_salary + bonus);
					increment(std::stof(value), tmp);
					break;

				case 4:
					check = false;
					break;
				}
			}

			auto itr1 = mp1.end();
			if (mp1.size() != 0) {
				itr1--;
			}
			for (auto it = mp1.begin(); it != mp1.end(); ++it) {
				query += it->first + " = " + it->second + " ,";
			}

			if (mp1.size() != 0) setAmount(base_salary + bonus);


			query += " amount = " + std::to_string(getAmount()) + " where Sid = " + tmp + " ;";
			//std::cout << query << "\n";


			rc = Database::getInstance().executeQuery(query.c_str());
			if (rc == 0) {
				std::cout << "Salary updated successfully\n\n";
				waitMenu();
			}
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
	}
}

void Salary::deleteSalary() {

}

void Salary::action() noexcept {
	auto check{ true };
	while (check) {
		system("cls");
		std::cout << "Select The Operation You Want The Perform\n";
		std::cout << "1. View\n";
		std::cout << "2. Update\n";
		std::cout << "3. Go to Main Menu\n\n";

		int i;
		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[1-3]" }));
		switch (i) {
		case 1:
			viewSalary();
			break;

		case 2:
			updateSalary();
			break;

		case 3:
			check = false;
			break;

		default:
			std::cout << "Enter Valid Choice\n";

		}
	}
}