#include "../include/DBmanage.h"

int DB::Database::row = 0;

bool DB::Database::open(const char* str) {
	rc = sqlite3_open(str, &db);
	const char* pragmaQuery = { "PRAGMA foreign_keys = ON;" };
	executeQuery(pragmaQuery);

	if (rc) {
		logging::default_logger()->log(logging::Log::Level::LevelError, sqlite3_errmsg(db));
		std::cerr << "\x1b[31mCan't open database: " << sqlite3_errmsg(db) << "\x1b[0m\n";
		return false;
	}
	else {
		logging::default_logger()->log(logging::Log::Level::LevelInfo, "Database Open Successfully");
		//std::cout << "Database Open Successfully \n";
		return true;
	}
}

bool DB::Database::createDefaultTables() {
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
		std::cerr << "\x1b[31mSQL error: " << errorMsg << "\x1b[0m" << std::endl;
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
		std::cerr << "\x1b[31mSQL error: " << errorMsg << "\x1b[0m" << std::endl;
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
		std::cerr << "\x1b[31mSQL error: " << errorMsg << "\x1b[0m" << std::endl;
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
		std::cerr << "\x1b[31mSQL error: " << errorMsg << "\x1b[0m" << std::endl;
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
		std::cerr << "\x1b[31mSQL error: " << errorMsg << "\x1b[0m" << std::endl;
		sqlite3_free(errorMsg);
	}
	else
	{
		logging::default_logger()->log(logging::Log::Level::LevelInfo, "Table created successfully");
		//std::cout << "Table created successfully" << std::endl;
	}

	return true;
}

int DB::Database::executeQuery(const char* sql, float count)
{
	rc = sqlite3_exec(db, sql, callbackForChecking, &count, &errorMsg);

	if (rc == 19) {
		//std::cerr << "You can not perform this operation on this record because this violates the rule of reference key constraints\n"; 
		//std::cout << "Press 0 to continue\n"; 
		//std::cin >> rc; 
		return rc;
	}
	else if (rc != SQLITE_OK)
	{
		std::cerr << "\x1b[31mSQL error: " << errorMsg << "\x1b[0m" << std::endl;
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
		std::cerr << "\x1b[31mSQL error: " << errorMsg << "\x1b[0m" << std::endl;
<<<<<<< HEAD
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
bool DB::Database::selectQueryForChecking(const char* sql)
{
	Database::row = 0;
	rc = sqlite3_exec(db, sql, callbackForChecking, 0, &errorMsg);

	if (rc != SQLITE_OK)
	{
		std::cerr << "\x1b[31mSQL error: " << errorMsg << "\x1b[0m" << std::endl;
=======
>>>>>>> 17217775496b21dd86a60f626a1c9ac79568d942
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
		//std::cerr << "Database Failed to close\n";
		return false;
	}
	else {
		logging::Info("Database closed Successfully");
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
		return 0;
	}
<<<<<<< HEAD
	return 0;
}

int DB::Database::callbackForChecking(void* data, int argc, char** argv, char** azColName) {
	Database::row++;
	return 0;
}
=======
	return 0;
}

int DB::Database::callbackOther(void* data, int argc, char** argv, char** azColName) {
	int* count = reinterpret_cast<int*>(data);
	*count = atoi(argv[0]);
	return 0;
}
>>>>>>> 17217775496b21dd86a60f626a1c9ac79568d942
