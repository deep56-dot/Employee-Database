#include "../include/Model/Salary.h"
#include "../include/Views/SalaryView.h"


double Model::Salary::increment(double percentage, int id) {
	try {
		double val = 0;
		std::string query = "select base_salary from Salary where Sid = " + std::to_string(id) + " ;";
		int rc = sqlite3_prepare_v2(DB::Database::getInstance().db, query.c_str(), -1, &DB::Database::getInstance().stmt, nullptr);
		rc = sqlite3_step(DB::Database::getInstance().stmt);
		if (rc == SQLITE_ROW) {
			val = sqlite3_column_double(DB::Database::getInstance().stmt, 0);
		}
		else {
		}

		val = (val + ((val * percentage) / 100));
		setBaseSalary(val);
		setAmount(base_salary + bonus);
		return amount;
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
		auto tmp =  SalaryViewer();

		if (tmp.has_value()) {
			auto& [field, value] = tmp.value();
			if (field == "id") {

				query += "select Employee.Eid , Employee.firstname , Employee.lastname , Employee.email , Salary.amount , Salary.base_salary , Salary.bonus from Employee JOIN Salary ON Employee.Eid = Salary.Sid where Sid = " + value + " ;";
			}
			else if (field == "all") {
				query += "select Employee.Eid , Employee.firstname , Employee.lastname , Employee.email , Salary.amount , Salary.base_salary , Salary.bonus from Employee JOIN Salary ON Employee.Eid = Salary.Sid ;";
			}

			DB::Database::getInstance().selectQuery(query.c_str());
			if (DB::Database::row == 0) {
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
		system("cls");

		// Uncomment for testing 
		/*std::string select = "select * from Salary where Sid = " + std::to_string(getId()) + ";";

		DB::Database::getInstance().selectQuery(select.c_str());

		if (DB::Database::row == 0) {
			std::cout << "\x1b[33m Employee is not in database \x1b[0m\n";
			waitMenu();
			return false;
		}*/

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

std::optional<Model::Salary> Model::Salary::getSalary(const std::string& id) {

	Salary s;
	auto callback = [](void* data, int argc, char** argv, char** azColName) {

		Salary* s1 = static_cast<Salary*>(data);
		s1->setId(argv[0] ? std::stoi(argv[0]) : -1);
		s1->setAmount(argv[1] ? std::stof(argv[1]) : -1);
		s1->setBaseSalary(argv[2] ? std::stof(argv[2]) : -1);
		s1->setBonus(argv[3] ? std::stof(argv[3]) : -1);

		return 0;
		};

	std::string selectQuery = "SELECT * FROM Salary WHERE Sid = " + id + ";";

	try {
		sqlite3_exec(DB::Database::getInstance().db, selectQuery.c_str(), callback, &s, 0);
	}
	catch (...) {
		return std::nullopt;
	}

	return s;

}