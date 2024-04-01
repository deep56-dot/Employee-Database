#ifndef _TABLE_
#define _TABLE_

#include<iostream>
#include<string>
#include<string_view>
#include<filesystem>
#include<fstream>
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
		void showTables() noexcept;
		bool deleteTable();
		void infoTable() noexcept;
		static std::optional<Table> getTable(const std::string& tableName);
		static std::vector<Model::Table> getAllTables();

		void writeCSV();
		bool exportToCsv(const std::string_view&, const std::filesystem::path&);

		bool insertRecord();
		bool updateRecord();
		bool deleteRecord() const;
		bool viewRecord() const;
		bool viewAllRecords() const;



		std::string getname() noexcept {
			return name;
		}

	private:
		std::string name;
		std::map<std::string, std::string> columnType;
		std::map<std::string, std::string> row;
	};
}

#endif