#include "../include/DBmanage.h"

int DB::Database::row = 0;

bool DB::Database::open(const char* str) {
	rc = sqlite3_open(str, &db);

	if (rc) {
		logging::default_logger()->log(logging::Log::Level::LevelError, sqlite3_errmsg(db));
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
		return false;
	}
	else {
		logging::default_logger()->log(logging::Log::Level::LevelInfo, "Database Open Successfully");
		//std::cout << "Database Open Successfully \n";
	}


	const char* sql = "CREATE TABLE IF NOT EXISTS Employee ("
		"Eid INTEGER PRIMARY KEY,"
		"firstname VARCHAR,"
		"lastname VARCHAR,"
		"dob DATE,"
		"mobile VARCHAR,"
		"email VARCHAR,"
		"address VARCHAR,"
		"gender VARCHAR CHECK (gender IN ('Male', 'Female', 'Other')),"
		"doj DATE,"
		"manager_id INTEGER,"
		"department_id INTEGER,"
		"FOREIGN KEY (department_id) REFERENCES Department(id),"
		"FOREIGN KEY (manager_id) REFERENCES Manager(id));";


	rc = sqlite3_exec(db, sql, 0, 0, &errorMsg);

	if (rc != SQLITE_OK)
	{
		logging::default_logger()->log(logging::Log::Level::LevelError, sqlite3_errmsg(db));
		std::cerr << "SQL error: " << errorMsg << std::endl;
		sqlite3_free(errorMsg);
	}
	else
	{
		logging::default_logger()->log(logging::Log::Level::LevelInfo, "Table created successfully");
		//std::cout << "Table created successfully" << std::endl;
	}

	const char* sql2 = "CREATE TABLE IF NOT EXISTS Department ("
		"id INTEGER PRIMARY KEY,"
		"Dname VARCHAR,"
		"manager_id INTEGER,"
		"description VARCHAR,"
		"FOREIGN KEY (manager_id) REFERENCES Manager(id))";

	rc = sqlite3_exec(db, sql2, 0, 0, &errorMsg);

	if (rc != SQLITE_OK)
	{
		logging::default_logger()->log(logging::Log::Level::LevelError, sqlite3_errmsg(db));
		std::cerr << "SQL error: " << errorMsg << std::endl;
		sqlite3_free(errorMsg);
	}
	else
	{
		logging::default_logger()->log(logging::Log::Level::LevelInfo, "Table created successfully");
		//std::cout << "Table created successfully" << std::endl;
	}


	const char* sql3 = "CREATE TABLE IF NOT EXISTS Engineer ("
		"id INTEGER PRIMARY KEY,"
		"programming_language VARCHAR,"
		"specialization VARCHAR,"
		"FOREIGN KEY (id) REFERENCES Employee(Eid) ON DELETE CASCADE )";

	rc = sqlite3_exec(db, sql3, 0, 0, &errorMsg);

	if (rc != SQLITE_OK)
	{
		logging::default_logger()->log(logging::Log::Level::LevelError, sqlite3_errmsg(db));
		std::cerr << "SQL error: " << errorMsg << std::endl;
		sqlite3_free(errorMsg);
	}
	else
	{
		logging::default_logger()->log(logging::Log::Level::LevelInfo, "Table created successfully");
		//std::cout << "Table created successfully" << std::endl;
	}

	const char* sql4 = "CREATE TABLE IF NOT EXISTS Manager ("
		"id INTEGER PRIMARY KEY,"
		"management_experience INTEGER,"
		"project_title VARCHAR,"
		"FOREIGN KEY (id) REFERENCES Employee(Eid) ON DELETE CASCADE)";

	rc = sqlite3_exec(db, sql4, 0, 0, &errorMsg);

	if (rc != SQLITE_OK)
	{
		logging::default_logger()->log(logging::Log::Level::LevelError, sqlite3_errmsg(db));
		std::cerr << "SQL error: " << errorMsg << std::endl;
		sqlite3_free(errorMsg);
	}
	else
	{
		logging::default_logger()->log(logging::Log::Level::LevelInfo, "Table created successfully");
		//std::cout << "Table created successfully" << std::endl;
	}

	const char* sql5 = "CREATE TABLE IF NOT EXISTS Salary ("
		"Sid INTEGER PRIMARY KEY,"
		"amount INTEGER,"
		"base_salary INTEGER,"
		"bonus INTEGER,"
		"FOREIGN KEY (Sid) REFERENCES Employee(Eid) ON DELETE CASCADE)  ";

	rc = sqlite3_exec(db, sql5, 0, 0, &errorMsg);

	if (rc != SQLITE_OK)
	{
		logging::default_logger()->log(logging::Log::Level::LevelError, sqlite3_errmsg(db));
		std::cerr << "SQL error: " << errorMsg << std::endl;
		sqlite3_free(errorMsg);
	}
	else
	{
		logging::default_logger()->log(logging::Log::Level::LevelInfo, "Table created successfully");
		//std::cout << "Table created successfully" << std::endl;
	}

	const char* pragmaQuery = { "PRAGMA foreign_keys = ON;" };
	executeQuery(pragmaQuery);

	return true;
}

void DB::Database::createTableQuery() {
	system("cls");
	std::cout << "If you want to go back press 0 Otherwise press 1\n";
	int i;
	if (std::cin >> i;  i == 0) {
		return;
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
	rc = executeQuery(sql.c_str());
	if (rc == 0) {
		std::cout << "\nTable created Suceesfully\n\n";
		waitMenu();
	}
	//std::cout << sql << "\n\n";

}

void DB::Database::showTables() {

	std::string showQuery = " SELECT name FROM sqlite_schema ;";

	rc = selectQuery(showQuery.c_str());

	waitMenu();
}

void DB::Database::deleteTableQuery() {
	system("cls");
	int i;
	std::cout << "Select the operation\n";
	std::cout << "0. To Go Back \n";
	std::cout << "1. Drop Table\n";
	std::cout << "2. Delete Data within table\n\n";
	i = std::stoi(input("Enter choice:", std::regex{ "[0-2]" }));
	std::string deleteQuery;
	std::string tableName;

	switch (i) {
	case 0:
		return;
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
		rc = executeQuery(deleteQuery.c_str());

		if (rc == 0) {
			std::cout << "Table Dropped Succesfully ! \n\n";
			waitMenu();
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
		rc = executeQuery(deleteQuery.c_str());
		if (rc == 0) {

			std::cout << "Table Deleted Succesfully ! \n\n";
			waitMenu();
		}
		break;

	default:
		std::cout << "Wrong Input..!\n\n";
		break;

	}

}

int DB::Database::executeQuery(const char* sql, float count)
{
	rc = sqlite3_exec(db, sql, callbackOther, &count, &errorMsg);

	if (rc == 19) {
		//std::cerr << "You can not perform this operation on this record because this violates the rule of reference key constraints\n"; 
		//std::cout << "Press 0 to continue\n"; 
		//std::cin >> rc; 
		return rc;
	}
	else if (rc != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errorMsg << std::endl;
		waitMenu();
		sqlite3_free(errorMsg);
		return rc;
	}
	else
	{
		//std::cout << "Query executed successfully" << std::endl;

		return rc;
		//return true;
	}


}

bool DB::Database::selectQuery(const char* sql)
{
	Database::row = 0;
	rc = sqlite3_exec(db, sql, callback, 0, &errorMsg);

	if (rc != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errorMsg << std::endl;
		std::cout << "Press Enter to continue\n";
		std::cin.get();
		sqlite3_free(errorMsg);
		return false;
	}
	else
	{
		//std::cout << "Query executed successfully" << std::endl;
		std::cout << Database::row << " row returned\n\n";
		return true;
	}
}

bool DB::Database::close() {
	rc = sqlite3_close(db);

	if (rc != SQLITE_OK) {
		std::cerr << "Database Failed to close\n";
		return false;
	}
	else {
		//std::cout << "Database closed Successfully\n";
		return true;
	}
}

int DB::Database::callback(void* data, int args, char** row, char** col) {
	//std::cout << "Hello from callback function\n";
	Database::row++;
	try {
		std::cout << "+--------------------------+----------------------------------------+" << std::endl;
		for (int i{ 0 }; i < args; i++) {
			std::cout << "|" << std::setw(25) << std::left << col[i] << " | " << std::setw(38) << std::left << (row[i] ? row[i] : "NULL") << " |" << std::endl;
		}
		std::cout << "+--------------------------+----------------------------------------+" << std::endl;
		std::cout << "\n";

		std::cout << "\n";
		return 0;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
	}
}

int DB::Database::callbackOther(void* data, int argc, char** argv, char** azColName) {
	int* count = reinterpret_cast<int*>(data);
	*count = atoi(argv[0]);
	return 0;
}

bool DB::Database::exportToCsv(const std::string_view& tableName, const std::filesystem::path& path) {

	std::ofstream file{ path , std::ios::app };

	if (!file.is_open()) {
		std::cout << "File is unable to open!!!!\n";
		waitMenu();
		return false;
	}

	std::string query = "select * from " + std::string{ tableName } + ";";
	rc = DB::Database::getInstance().executeQuery(query.c_str());

	if (rc != 0) {
		std::cout << "Error msg: " << errorMsg << "\n";
		waitMenu();
		return false;
	}

	stmt = nullptr;

	int rc = sqlite3_prepare_v2(DB::Database::getInstance().db, query.c_str(), -1, &DB::Database::getInstance().stmt, nullptr);
	if (rc != 0) {
		std::cout << "Error msg: " << errorMsg << "\n";
		waitMenu();
		return false;
	}

	int columnsCount = sqlite3_column_count(stmt);


	file << "\n" << logging::Log::cacheTime() << "\n\n";

	for (auto i{ 0 }; i < columnsCount; i++) {
		file << sqlite3_column_name(stmt, i);
		if (i != columnsCount - 1) {
			file << ",";
		}
	}
	file << ";\n";

	while (rc = sqlite3_step(stmt), rc == 100) {
		for (auto i{ 0 }; i < columnsCount; i++) {
			file << sqlite3_column_text(stmt, i);
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
}

void DB::Database::writeCSV() {
	std::filesystem::path p{ "C:\\Users\\ZTI\\OneDrive - ZURU INC\\C++ Training\\DatabaseManagement\\DatabaseManagement\\Backup\\Employee.csv" };
	if (!DB::Database::getInstance().exportToCsv("Employee", p)) {
		waitMenu();
		return;
	}

	p = "C:\\Users\\ZTI\\OneDrive - ZURU INC\\C++ Training\\DatabaseManagement\\DatabaseManagement\\Backup\\Engineer.csv";
	if (!DB::Database::getInstance().exportToCsv("Engineer", p)) {
		waitMenu();
		return;
	}

	p = "C:\\Users\\ZTI\\OneDrive - ZURU INC\\C++ Training\\DatabaseManagement\\DatabaseManagement\\Backup\\Manager.csv";
	if (!DB::Database::getInstance().exportToCsv("Manager", p)) {
		waitMenu();
		return;
	}

	p = "C:\\Users\\ZTI\\OneDrive - ZURU INC\\C++ Training\\DatabaseManagement\\DatabaseManagement\\Backup\\Department.csv";
	if (!DB::Database::getInstance().exportToCsv("Department", p)) {
		waitMenu();
		return;
	}

	p = "C:\\Users\\ZTI\\OneDrive - ZURU INC\\C++ Training\\DatabaseManagement\\DatabaseManagement\\Backup\\Salary.csv";
	if (!DB::Database::getInstance().exportToCsv("Salary", p)) {
		waitMenu();
		return;
	}

	waitMenu();
}