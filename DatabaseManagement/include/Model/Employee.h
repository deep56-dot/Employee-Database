#ifndef _Employee_
#define _Employee_

#include <iostream>
#include <string>
#include <map>
#include "Salary.h"
#include "../DBmanage.h"
#include "../Helper.h"
#include"../Regex.h"


enum class Gender { Male, Female, Other };

using namespace std;

class Employee {

public:
    Employee() = default;
    Employee(int id, const std::string_view& firstname, const std::string_view& lastname, const std::string_view& dob,
        const std::string_view& mobile, const std::string_view& email, const std::string_view& address,
        Gender gender, const std::string_view& doj,
        int manager_id, int department_id , Salary s1)
        : Eid(id), firstname(firstname), lastname(lastname), dob(dob), mobile(mobile), email(email),
        address(address), gender(gender), doj(doj), 
        manager_id(manager_id), department_id(department_id), s{s1} {}

    int getId() const { return Eid; }
    std::string getFirstname() const { return firstname; }
    std::string getLastname() const { return lastname; }
    std::string getDob() const { return dob; }
    std::string getMobile() const { return mobile; }
    std::string getEmail() const { return email; }
    std::string getAddress() const { return address; }
    Gender getGender() const { return gender; }
    std::string getDoj() const { return doj; }
    int getManagerId() const { return manager_id; }
    int getDepartmentId() const { return department_id; }

    void setId(const int& id)  { Eid = id; }
    void setFirstname(const std::string_view& str)  {  firstname = str; }
    void setLastname(const std::string_view& str)  { lastname = str; }
    void setDob(const std::string_view& str) { dob = str; }
    void setMobile(const std::string_view& str) { mobile = str; }
    void setEmail(const std::string_view& str) { email = str; }
    void setAddress()  { 
        std::string add;
        std::string msg = " Enter # to leave the field Empty\n"; 
        std::cout << "Enter address: "+msg;
        std::cin.ignore(); 
        std::getline(std::cin, add);
        if (add == "#") add = "";
        address = add;
    }
    void setGender(const Gender& g) { gender = g; }
    void setDoj(const std::string_view& str)  { doj = str; } 
    void setManagerId(const int& id)  {  manager_id = id; } 
    void setDepartmentId(const int& id)  {  department_id = id; } 


    void viewEmployee();
    void insertEmployee();
    void deleteEmployee();
    void updateEmployee();
    void userInputEmployee();
    void action() noexcept;


private:
    int Eid;
    std::string firstname{};
    std::string lastname{};
    std::string dob{};
    std::string mobile{};
    std::string email{};
    std::string address{};
    Gender gender{};
    std::string doj{};
    int manager_id{};
    int department_id{};
    Salary s;
};
#endif 