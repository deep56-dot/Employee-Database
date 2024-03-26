#include "../include/Model/Salary.h"

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

double Salary::increment(double percentage, int id) {
	try {
		double val = 0;
		std::string query = "select base_salary from Salary where Sid = " + std::to_string(id) + " ;";
		int rc = sqlite3_prepare_v2(Database::getInstance().db, query.c_str(), -1, &Database::getInstance().stmt, nullptr);
		rc = sqlite3_step(Database::getInstance().stmt);
		if (rc == SQLITE_ROW) {
			
			val = sqlite3_column_double(Database::getInstance().stmt, 0);
		
		}
		else {
			//std::cerr << "No rows returned" << std::endl;
		}

		val = (val + ((val * percentage) / 100));
		setBaseSalary(val);
		setAmount(base_salary + bonus);
		return amount;
		//std::cout << amount << "\n";
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return 0.0;
	}
}

bool Salary::viewSalary() {
	try {
		system("cls");
		std::string query = "select Employee.Eid , Employee.firstname , Employee.lastname , Employee.email , Salary.amount , Salary.base_salary , Salary.bonus from Employee JOIN Salary ON Employee.Eid = Salary.Sid where Sid =  ";
		std::string tmp;
		std::cout << "Enter Eid to view salary :";
		std::cin >> tmp;
		query += tmp + " ;";
		Database::getInstance().selectQuery(query.c_str());
		if (Database::row == 0) {
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

bool Salary::insertSalary(int id) const {
	try {
		std::string query = "insert into Salary values(" + std::to_string(id) + " , " + std::to_string(getAmount()) + " , " + std::to_string(getBaseSalary()) + " ," + std::to_string(getBonus()) + ") ;";
		//std::cout << query; 
		Database::getInstance().executeQuery(query.c_str());
		return true;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

bool Salary::updateSalary() {
	try {
		system("cls");

		setId(std::stoi(input( "Enter the Eid to update Salary : "))); 

		std::string select = "select * from Salary where Sid = " + std::to_string(getId()) + " ;";
		Database::getInstance().selectQuery(select.c_str());
		if (Database::row == 0) {
			std::cout << "Entered Employee is not in database\n\n";
			std::cout << "Press 0 to continue\n";
			int i;
			std::cin >> i;
			return false;
		}
		else {
			std::string query1 = "select base_salary from Salary where Sid = " + std::to_string(Sid) + " ;";
			int rc = sqlite3_prepare_v2(Database::getInstance().db, query1.c_str(), -1, &Database::getInstance().stmt, nullptr);
			rc = sqlite3_step(Database::getInstance().stmt);
			base_salary = sqlite3_column_double(Database::getInstance().stmt, 0);

			query1 = "select bonus from Salary where Sid = " + std::to_string(Sid) + " ;";
			rc = sqlite3_prepare_v2(Database::getInstance().db, query1.c_str(), -1, &Database::getInstance().stmt, nullptr);
			rc = sqlite3_step(Database::getInstance().stmt);
			bonus = sqlite3_column_double(Database::getInstance().stmt, 0);

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
					return true;

				case 1:
					setBaseSalary(std::stof(input("Enter Base Salary: ", salaryRegex))); 
					break;

				case 2:
					setBonus(std::stof(input("Enter Bonus: ", salaryRegex)));
					break;

				case 3:
					value = input("Enter Percantage by which you want to increase the salary :");
					increment(std::stof(value), getId());
					break;

				case 4:
					check = false;
					break;
				}
			}

			setAmount(base_salary + bonus);
			std::string query = "update Salary set amount = " + std::to_string(amount) + "  , base_salary = " + std::to_string(base_salary) + " , bonus = " + std::to_string(bonus) + " where Sid = " + std::to_string(Sid) + "; ";
			//std::cout << query << "\n";  

			rc = Database::getInstance().executeQuery(query.c_str());
			if (rc == 0) {
				std::cout << "Salary updated successfully\n\n";
				waitMenu();
				logging::Info("Salary updated for Id: ", std::to_string(getId()));

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

bool Salary::deleteSalary() {
	return true;
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