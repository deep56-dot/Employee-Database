#ifndef _Dep_
#define _Dep_


#include <iostream>
#include <string>
#include <string_view>
#include <map>
#include "../DBmanage.h"
#include "../Helper.h"
#include"../Regex.h"
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

    void setName() {
        std::string desc; 
        std::string msg = " Enter # to leave the field Empty\n"; 
        std::cout << "Enter Department Name: " + msg; 
        std::cin.ignore(); 
        std::getline(std::cin , desc); 
        if (desc == "#") desc = ""; 
        Dname = desc; 
    }

    void setManagerId(const int& mId) {
        manager_id = mId;
    }

    void setDescription() {
        std::string desc;
        std::string msg = " Enter # to leave the field Empty\n";
        std::cout << "Enter description: " + msg;
        std::cin.ignore();
        std::getline(std::cin, desc);
        if (desc == "#") desc = "";
        description = desc;
    }

    void viewDepartment();
    void insertDepartment();
    void deleteDepartment();
    void updateDepartment();
    void userInput();
    void action() noexcept;

private:

    int Did;
    std::string Dname;
    int manager_id;
    std::string description;
};
#endif