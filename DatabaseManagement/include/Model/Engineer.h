#ifndef _Engineer_
#define _Engineer_

#include "Employee.h"
//#include "../DBmanage.h"
class Engineer : public Employee {
public:
    Engineer() = default;
    Engineer(int id, const std::string_view& firstname, const std::string_view& lastname, const std::string_view& dob,
        const std::string_view& mobile, const std::string_view& email, const std::string_view& address,
        Gender gender, const std::string_view& doj,int manager_id, int department_id,Salary s ,const std::string_view& programming_language,
        const std::string_view& specialization)
        : Employee(id, firstname, lastname, dob, mobile, email, address, gender, doj, manager_id, department_id , s),
        programming_language(programming_language), specialization(specialization) {}


    std::string getProgrammingLanguage() const { return programming_language; }
    std::string getSpecialization() const { return specialization; }

    void setProgramming_language(const std::string_view& lang) { programming_language = lang; }
    void setSpecialization() {
        std::string specs; 
        std::string msg = " Enter # to leave the field Empty\n"; 
        std::cout << "Enter Specialization: "+msg;
        std::cin.ignore(); 
        std::getline(std::cin, specs); 
        if (specs == "#") specs = "";
        specialization = specs; 
    }

    void viewEngineer();
    void insertEngineer();
    void deleteEngineer();
    void updateEngineer();
    void userInputEngineer();
    void action() noexcept;

private:

    std::string programming_language;
    std::string specialization;
};
#endif