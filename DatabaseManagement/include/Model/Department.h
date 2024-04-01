#ifndef _Dep_
#define _Dep_


#include <iostream>
#include <utility>
#include <string>
#include <string_view>
#include <unordered_map>
#include "../DBmanage.h"
#include "../Helper.h"
#include"../Regex.h"
#include "../LOG/log.h"
#include "../LOG/logger.h"

using namespace utility;

namespace Model {
	class Department {
	public:
		Department() = default;
		Department(int id, const std::string_view& name, int manager_id, const std::string_view& description)
			: Did(id), Dname(name), manager_id(manager_id), description(description) {}

		int getId() const { return Did; }
		std::string getName() const { return Dname; }
		int getManagerId() const { return manager_id; }
		std::string getDescription() const { return description; }

		void setId(const int& id1) {
			Did = id1;
		}
		void setName(const std::string_view& name) {
			Dname = name;
		}
		void setManagerId(const int& mId) {
			manager_id = mId;
		}
		void setDescription(const std::string_view& desc) {
			description = desc;
		}

		static std::optional<Department> getDepartment(const std::string& id);
<<<<<<< HEAD
		bool viewDepartment() const;
		bool insertDepartment() const;
		bool deleteDepartment() const;
		bool updateDepartment() const;
=======
		bool viewDepartment();
		bool insertDepartment();
		bool deleteDepartment();
		bool updateDepartment();
>>>>>>> 17217775496b21dd86a60f626a1c9ac79568d942

	private:

		int Did{};
		std::string Dname{};
		int manager_id{};
		std::string description{};
	};

}
#endif