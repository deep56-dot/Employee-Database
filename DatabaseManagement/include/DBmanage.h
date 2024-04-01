#ifndef _DB_
#define _DB_

#include<iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "../include/Helper.h"
#include "../sqlite/sqlite3.h"
#include "LOG/log.h"
#include "LOG/logger.h"

using namespace utility;

namespace DB {
	class Database {

		Database() = default;
		~Database() {
			close();
		}
		Database(const Database&) = delete;
		Database& operator=(const Database&) = delete;

	public:
		char* errorMsg = 0;
		sqlite3* db{};
		int rc{ 0 };
		sqlite3_stmt* stmt{};

		static int row;

		bool open(const char* str);
		bool createDefaultTables();
		bool close();
		int executeQuery(const char* sql, float count = 0);
		bool selectQuery(const char* sql);
		bool selectQueryForChecking(const char* sql);

		static Database& getInstance() {
			static Database db;
			return db;
		}


		static int callback(void* data, int args, char** row, char** col);
		static int callbackForChecking(void* data, int args, char** row, char** col);
	};
}



#endif