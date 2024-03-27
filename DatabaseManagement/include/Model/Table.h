#ifndef _TABLE_
#define _TABLE_

#include<iostream>
#include<string>
#include<string_view>
#include<vector>
#include<map>
#include<optional>
#include<array>
#include "../DBmanage.h"
#include "../Helper.h"
#include "../Regex.h"

inline constexpr std::array<std::string_view, 5> numericType{ "int" , "integer" , "float" , "INT" , "INTEGER" };

namespace Model {
	class Table {

	public:
		bool createTable();
		void showTables();
		bool deleteTable();
		void infoTable();

		bool insertRecord();
		bool deleteRecord();
		bool updateRecord();
		bool viewRecord();
		bool viewAllRecords();
		static std::optional<Table> getTable(const std::string& tableName);
		static std::vector<Model::Table> getAllTables();

		void writeCSV();
		bool exportToCsv(const std::string_view&, const std::filesystem::path&);

		void action();

	private:
		std::string name;
		std::map<std::string, std::string> columnType;
		std::map<std::string, std::string> row;
	};
}

#endif
