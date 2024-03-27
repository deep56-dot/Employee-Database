#include "../include/Model/Table.h"

bool Model::Table::createTable() {
	system("cls");
	std::cout << "If you want to go back press 0 Otherwise press 1\n";
	int i;
	if (std::cin >> i;  i == 0) {
		return false;
	}
	std::string tableName;
	std::cout << "Enter table name: ";
	std::cin >> tableName;
	std::string sql = "CREATE TABLE IF NOT EXISTS " + tableName + " (";
	std::vector<std::string> columns;

	char choice;

	do {
		std::string columnName, columnType, constraints;
		std::cout << "\nEnter column name: ";
		std::cin >> columnName;
		std::cout << "Enter column type: ";
		std::cin >> columnType;
		std::cout << "Enter column constraints : ";
		std::cin.ignore();
		std::getline(std::cin, constraints);

		columns.push_back(columnName + " " + columnType + " " + constraints);
		std::cout << "Add another column? (y/n): ";
		std::cin >> choice;

	} while (choice == 'y' || choice == 'Y');

	for (int i = 0; i < columns.size(); ++i) {
		sql += columns[i];
		if (i < columns.size() - 1) {
			sql += ",";
		}
	}
	sql += ");";

	//std::cout << sql;
	int rc = DB::Database::getInstance().executeQuery(sql.c_str());
	if (rc == 0) {
		std::cout << "\nTable created Suceesfully\n\n";
		waitMenu();
		return true;
	}
	//std::cout << sql << "\n\n";
	return false;
}

void Model::Table::showTables() {

	std::string showQuery = " SELECT name FROM sqlite_schema ;";

	int rc = DB::Database::getInstance().selectQuery(showQuery.c_str());

	waitMenu();
}

bool Model::Table::deleteTable() {
	system("cls");
	int i;
	int rc;
	std::cout << "Select the operation\n";
	std::cout << "0. To Go Back \n";
	std::cout << "1. Drop Table\n";
	std::cout << "2. Delete Data within table\n\n";
	i = std::stoi(input("Enter choice:", std::regex{ "[0-2]" }));
	std::string deleteQuery;
	std::string tableName;

	switch (i) {
	case 0:
		return false;
		break;
	case 1:
		std::cout << "\nEnter Table Name to Drop: ";
		std::cin >> tableName;
		if (tableName == "Employee" || tableName == "Salary" || tableName == "Engineer" || tableName == "Manager" || tableName == "Department") {
			std::cout << " \x1b[31mYou can not delete this Table\x1b[0m\n";
			waitMenu();
			break;
		}
		deleteQuery = "DROP TABLE " + tableName + ";";
		//std::cout << deleteQuery << "\n\n";
		rc = DB::Database::getInstance().executeQuery(deleteQuery.c_str());

		if (rc == 0) {
			std::cout << "Table Dropped Succesfully ! \n\n";
			waitMenu();
			return true;
		}
		break;

	case 2:

		std::cout << "\nEnter Table Name to Delete: ";
		std::cin >> tableName;
		if (tableName == "Employee" || tableName == "Salary" || tableName == "Engineer" || tableName == "Manager" || tableName == "Department") {
			std::cout << "\x1b[31mYou can not delete this Table\x1b[0m\n";
			waitMenu();
			break;
		}
		deleteQuery = "DELETE FROM " + tableName + ";";
		//std::cout << deleteQuery << "\n\n";
		rc = DB::Database::getInstance().executeQuery(deleteQuery.c_str());
		if (rc == 0) {

			std::cout << "Table Deleted Succesfully ! \n\n";
			waitMenu();
			return true;
		}
		break;

	default:
		std::cout << "Wrong Input..!\n\n";
		break;

	}

	return false;

}

std::optional<Model::Table> Model::Table::getTable(const std::string& tableName) {
	std::string query = "PRAGMA table_info ( " + tableName + " ) ;";

	Table t;
	t.name = tableName;

	sqlite3_exec(DB::Database::getInstance().db, query.c_str(), [](void* data, int argc, char** argv, char** azColName) mutable -> int {

		auto columns = static_cast<std::map<std::string, std::string>*> (data);

		columns->insert({ argv[1] , argv[2] ? argv[2] : "NULL" });

		return 0;
		}, &t.columnType, &DB::Database::getInstance().errorMsg);

	if (t.columnType.size() == 0) return {};
	return t;
}

std::vector<Model::Table> Model::Table::getAllTables() {
	std::vector<Model::Table> tables;

	//std::string query = "SELECT name FROM sqlite_master WHERE type = 'table';";
	std::string query = " SELECT name FROM sqlite_schema ;";

	int rc = sqlite3_exec(DB::Database::getInstance().db, query.c_str(), [](void* data, int argc, char** argv, char** col) mutable -> int {
		auto list = static_cast<std::vector<Model::Table>*>(data);

		auto t = Model::Table::getTable(argv[0]);
		if (t.has_value()) {
			list->push_back(t.value());
		}
		return 0;
		}
	, &tables, &DB::Database::getInstance().errorMsg);

	return tables;
}

void Model::Table::infoTable() {
	std::cout << "\n" << name << "\n";

	std::cout << "+--------------------------+----------------------------------------+" << std::endl;
	for (auto& [key, value] : columnType) {
		std::cout << "|" << std::setw(25) << std::left << key << " | " << std::setw(38) << std::left << value << " |" << std::endl;
	}
	std::cout << "+--------------------------+----------------------------------------+" << std::endl;
	waitMenu();
}

bool Model::Table::insertRecord() {
	row.clear();

	for (auto& [field, type] : columnType) {
		if (std::find(numericType.begin(), numericType.end(), type) != numericType.end()) {
			auto value = input("Enter " + field + ": ", idRegex);
			row.insert({ field , value });
		}
		else {
			auto value = input("Enter " + field + " : ", alphaRegex);
			row.insert({ field , value });
		}
	}

	std::string query = "insert into " + name + " (";

	for (auto& [field, type] : columnType) {
		query += field + ",";
	}

	query.erase(query.find_last_of(','), 1);

	query += " ) values ( ";

	for (auto& [field, value] : row) {
		if (std::find(numericType.begin(), numericType.end(), columnType[field]) != numericType.end()) {
			query += value + ",";
		}
		else {
			query += "'" + value + "' ,";
		}
	}
	query.erase(query.find_last_of(','), 1);
	query += " ) ; ";

	int rc = DB::Database::getInstance().executeQuery(query.c_str());

	if (rc == 0) {
		std::cout << "In " + name + ": Record Inserted successfully!!!!\n";
		waitMenu();
		return true;
	}
	return false;
}

bool Model::Table::deleteRecord() {
	auto id = input("Enter id to delete records:", idRegex);

	std::string query = "delete from " + name + " where id = " + id + " ;";

	int rc = DB::Database::getInstance().executeQuery(query.c_str());
	if (rc == 0) {
		std::cout << "Record deleted successfully from " + name + "\n";
		waitMenu();
		return true;
	}
	return false;
}

bool Model::Table::updateRecord() {

	row.clear();

	auto id = input("Enter id to update record: ", idRegex);

	std::cout << "Enter # to keep the field as it is \n\n";

	for (auto& [field, type] : columnType) {

		if (field == "id") continue;
		if (std::find(numericType.begin(), numericType.end(), type) != numericType.end()) {
			auto value = input("Enter " + field + ": ",idRegex, true);
			if (value == "0") continue;
			row.insert({ field , value });
		}
		else {
			auto value = input("Enter " + field + ": ", alphaRegex);
			if (value == "") continue;
			row.insert({ field , value });
		}
	}

	
	std::string query;
	if (row.size() != 0) {
	    query = "update " + name + " set ";
		for (auto& [key, val] : row) {
			if (std::find(numericType.begin(), numericType.end(), columnType[key]) != numericType.end()) {
				if (key == "id") continue;
				query += (key + "=" + val + ",");
			}
			else {
				query += (key + "= '" + val + "' ,");
			}
		}
		query.erase(query.find_last_of(','), 1);
	}
	int rc = DB::Database::getInstance().executeQuery(query.c_str());
	query += " where id = " + id + " ;";
	std::cout << query<<"\n";
	if (rc == 0) {
		std::cout << "in " + name + "Record updated successfully with id " + id<<"\n";
		waitMenu();
		return true;
	}
	return false;
}

bool Model::Table::viewRecord() {
	auto id = input("Enter id to view records: ", idRegex);

	std::string query = "select * from " + name + " where id = " + id + " ;";
	int rc = DB::Database::getInstance().selectQuery(query.c_str());
	waitMenu();
	return true;
}

bool Model::Table::viewAllRecords() {

	std::string query = "select * from " + Model::Table::name + "; ";

	int rc = DB::Database::getInstance().selectQuery(query.c_str());
	waitMenu();
	return true;
}

bool Model::Table::exportToCsv(const std::string_view& tableName, const std::filesystem::path& path) {

	std::ofstream file{ path , std::ios::app };

	if (!file.is_open()) {
		std::cout << "File is unable to open!!!!\n";
		waitMenu();
		return false;
	}

	std::string query = "select * from " + std::string{ tableName } + ";";
	auto rc = DB::Database::getInstance().executeQuery(query.c_str());

	if (rc != 0) {
		std::cout << "Error msg: " << DB::Database::getInstance().errorMsg << "\n";
		waitMenu();
		return false;
	}

	DB::Database::getInstance().stmt = nullptr;

	 rc = sqlite3_prepare_v2(DB::Database::getInstance().db, query.c_str(), -1, &DB::Database::getInstance().stmt, nullptr);
	if (rc != 0) {
		std::cout << "Error msg: " << DB::Database::getInstance().errorMsg << "\n";
		waitMenu();
		return false;
	}

	int columnsCount = sqlite3_column_count(DB::Database::getInstance().stmt);


	file << "\n" << logging::Log::cacheTime() << "\n\n";

	for (auto i{ 0 }; i < columnsCount; i++) {
		file << sqlite3_column_name(DB::Database::getInstance().stmt, i);
		if (i != columnsCount - 1) {
			file << ",";
		}
	}
	file << ";\n";

	while (rc = sqlite3_step(DB::Database::getInstance().stmt) ,rc== 100) {
		for (auto i{ 0 }; i < columnsCount; i++) {
			file << sqlite3_column_text(DB::Database::getInstance().stmt, i);
			if (i != columnsCount - 1) {
				file << ",";
			}
		}
		file << ";\n";
	}

	if (rc == 101) {
		std::cout << "Table " + std::string{ tableName } + " backup successfull!!!!\n";
		logging::Info("Table " + std::string{ tableName } + " backup successfull!!!!");
		return true;
	}
	return false;
}

void Model::Table::writeCSV() {
	std::filesystem::path p{ "C:\\Users\\ZTI\\OneDrive - ZURU INC\\C++ Training\\DatabaseManagement\\DatabaseManagement\\Backup\\" };
	auto tables = Model::Table::getAllTables();
	for (auto it : tables) {
		auto path = p;
		path /= it.name + ".csv";
		if (!Model::Table::exportToCsv(it.name, path)) {
			waitMenu();
			return;
		}
	}

	waitMenu();
}

void Model::Table::action() {
	auto tables = Model::Table::getAllTables();
	for (auto& it:tables) {
		std::cout << "->"<<it.name<<"\n";
	}
	std::cout << "Enter Table Name You Want To Interact\n";
	std::string tablename;
	std::cin >> tablename;
	auto t = Model::Table::getTable(tablename);
	if (t.has_value()) {
		auto ch{ true };
		while (ch) {
			system("cls");
			std::cout << "Enter the Opertaion you want to perform\n";
			std::cout << "1. view record\n";
			std::cout << "2. view all records\n";
			std::cout << "3. insert record\n";
			std::cout << "4. update record\n";
			std::cout << "5. delete record\n";
			std::cout << "6. show schema\n";
			std::cout << "7. Exit\n\n";

			int i;
			i = std::stoi(input("Enter Choice: ", std::regex{ "[1-7]" }));
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

			default:
				std::cout << "Enter valid input: \n";
			}
		}
		
	}
	else {
		system("cls");
		std::cout << " Table With Name"<<tablename<<" Not Avialable\n";
		waitMenu();
	}
}