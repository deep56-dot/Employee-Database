#include "../include/Model/Salary.h"
std::optional<Model::Salary> updateSalaryViewer();
std::optional<int> SalaryViewer();
//std::optional<string> Model::Salary::userInputSalary() {
//
//	try {
//		std::string msg = " Enter # to leave the field Empty: \n";
//
//		if (auto tmp = input("Enter Base Salary OR " + msg, salaryRegex, true); tmp.has_value()) setBaseSalary(std::stof(tmp.value()));
//		else return false;
//
//		if (auto tmp = input("Enter Bonus OR " + msg, salaryRegex, true); tmp.has_value()) setBonus(std::stof(tmp.value()));
//		else return false;
//
//		setAmount(base_salary + bonus);
//		return true;
//	}
//	catch (std::exception& e) {
//		std::cout << e.what() << std::endl;
//		waitMenu();
//		return false;
//	}
//}

double Model::Salary::increment(double percentage, int id) {
	try {
		double val = 0;
		std::string query = "select base_salary from Salary where Sid = " + std::to_string(id) + " ;";
		int rc = sqlite3_prepare_v2(DB::Database::getInstance().db, query.c_str(), -1, &DB::Database::getInstance().stmt, nullptr);
		rc = sqlite3_step(DB::Database::getInstance().stmt);
		if (rc == SQLITE_ROW) {
			// Get the value of the 'amount' column
			val = sqlite3_column_double(DB::Database::getInstance().stmt, 0);
			//std::cout << "Amount: " << val << std::endl;
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

bool Model::Salary::viewSalary() {
	try {
		system("cls");
		std::string query;
		auto tmp = SalaryViewer();
		if(tmp.has_value())
		{
			std::cout << tmp.value();
			std::string query = "select Employee.Eid , Employee.firstname , Employee.lastname , Employee.email , Salary.amount , Salary.base_salary , Salary.bonus from Employee JOIN Salary ON Employee.Eid = Salary.Sid where Sid = " + std::to_string(tmp.value()) + ";";
			
			DB::Database::getInstance().selectQuery(query.c_str());
			if (DB::Database::row == 0) {
				waitMenu();
				return false;
			}
			waitMenu();
			return true;
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
}

bool Model::Salary::insertSalary(int id) const {
	try {
		std::string query = "insert into Salary values(" + std::to_string(id) + " , " + std::to_string(getAmount()) + " , " + std::to_string(getBaseSalary()) + " ," + std::to_string(getBonus()) + ") ;";
		//std::cout << query; 
		DB::Database::getInstance().executeQuery(query.c_str());
		return true;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return false;
	}
}

bool Model::Salary::updateSalary() {
	try {
		auto tmp = updateSalaryViewer();
		//auto tmp = Model::Employee::getEmployee(std::to_string(id));  // For testing
		if (tmp.has_value()) {

			*this = tmp.value();

			setAmount(base_salary + bonus);
			std::string query = "update Salary set amount = " + std::to_string(amount) + "  , base_salary = " + std::to_string(base_salary) + " , bonus = " + std::to_string(bonus) + " where Sid = " + std::to_string(Sid) + "; ";
			//std::cout << query << "\n";  

			int rc = DB::Database::getInstance().executeQuery(query.c_str());
			if (rc == 0) {
				std::cout << "\x1b[32mSalary updated successfully\x1b[0m\n\n";
				waitMenu();
				logging::Info("Salary updated for Id: ", std::to_string(getId()));

				return true;
			}
			return false;
		}
		else {
			std::cerr << "\x1b[33m Updation Failed \x1b[0m\n\n";
			waitMenu();
			return false;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "\x1b[33m Updation Failed!!! \x1b[0m\n";
		waitMenu();
		return false;
	}
}

bool Model::Salary::deleteSalary() {
	return true;
}

void Model::Salary::action() noexcept {
	auto check{ true };
	while (check) {
		system("cls");
		std::cout << "Select The Operation You Want The Perform\n";
		std::cout << "1. View\n";
		std::cout << "2. Update\n";
		std::cout << "3. Go to Main Menu\n\n";

		int i;
		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[1-3]" }).value_or("3"));
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

std::optional<Model::Salary> Model::Salary::getSalary(const std::string& id) {

	Salary e;
	auto callback = [](void* data, int argc, char** argv, char** azColName) {

		Salary* d1 = static_cast<Salary*>(data);
		d1->setId(argv[0] ? std::stoi(argv[0]) : -1);
		d1->setAmount(argv[1] ? std::stof(argv[1]) : -1);
		d1->setBaseSalary(argv[2] ? std::stof(argv[2]) : -1);
		d1->setBonus(argv[3] ? std::stof(argv[3]) : -1);

		return 0;
		};

	std::string selectQuery = "SELECT * FROM Salary WHERE Sid = " + id + ";";

	try {
		sqlite3_exec(DB::Database::getInstance().db, selectQuery.c_str(), callback, &e, 0);
	}
	catch (...) {
		return std::nullopt;
	}

	return e;
}