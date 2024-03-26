#ifndef _Engineer_
#define _Engineer_

#include "Employee.h"
#include "../LOG/log.h"
#include "../LOG/logger.h"

class Engineer : public Employee {
public:
    Engineer() = default;
    Engineer(int id, const std::string firstname, const std::string lastname, const std::string dob,
        const std::string mobile, const std::string email, const std::string address,
        Gender gender, const std::string doj, int manager_id, int department_id, Salary s, const std::string programming_language,
        const std::string specialization)
        : Employee(id, firstname, lastname, dob, mobile, email, address, gender, doj, manager_id, department_id, s),
        programming_language(programming_language), specialization(specialization) {}


    std::string getProgrammingLanguage() const { return programming_language; }
    std::string getSpecialization() const { return specialization; }

    void setProgramming_language(const std::string lang) { programming_language = lang; }
    void setSpecialization() {
        std::string specs;
        std::string msg = " Enter # to leave the field Empty\n";
        std::cout << "Enter Specialization: " + msg;
        std::cin.ignore();
        std::getline(std::cin, specs);
        if (specs == "#") specs = "";
        specialization = specs;
    }

    bool viewEngineer();
    bool insertEngineer();
    bool deleteEngineer();
    bool updateEngineer();
    void userInputEngineer();
    void action() noexcept;

private:

    std::string programming_language;
    std::string specialization;
};
#endif