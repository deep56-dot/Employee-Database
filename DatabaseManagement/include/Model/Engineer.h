#ifndef _Engineer_
#define _Engineer_

#include "Employee.h"
#include "../LOG/log.h"
#include "../LOG/logger.h"

namespace Model {
    class Engineer : public Model::Employee {
    public:
        Engineer() = default;
        Engineer(int id, const std::string_view& firstname, const std::string_view& lastname, const std::string_view& dob,
            const std::string_view& mobile, const std::string_view& email, const std::string_view& address,
            Gender gender, const std::string_view& doj, int manager_id, int department_id, Salary s, const std::string_view& programming_language,
            const std::string_view& specialization)
            : Employee(id, firstname, lastname, dob, mobile, email, address, gender, doj, manager_id, department_id, s),
            programming_language(programming_language), specialization(specialization) {}


        std::string getProgrammingLanguage() const { return programming_language; }
        std::string getSpecialization() const { return specialization; }

        void setProgramming_language(const std::string_view& lang) { programming_language = lang; }
        void setSpecialization(const std::string_view& specs) { specialization = specs; }

        bool viewEngineer();
        bool insertEngineer();
        bool deleteEngineer();
        bool updateEngineer();
        bool userInputEngineer();
        void action() noexcept;

    private:
        std::string programming_language;
        std::string specialization;
    };
}

#endif