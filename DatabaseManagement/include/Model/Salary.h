#ifndef _Salary_
#define _Salary_
#include <iostream> 
#include <map> 
#include "../Helper.h"
#include "../Regex.h"
#include "../DBmanage.h"
#include "../LOG/log.h"
#include "../LOG/logger.h"

using namespace utility;

namespace Model {
    class Salary {
    public:

        Salary() = default;
        Salary(int id, double amount, double base_salary, double bonus)
            : Sid(id), amount(amount), base_salary(base_salary), bonus(bonus) {}

        int getId() const { return Sid; }
        double getAmount() const { return amount; }
        double getBaseSalary() const { return base_salary; }
        double getBonus() const { return bonus; }

        void setId(int id) { Sid = id; }
        void setAmount(double figure) {
            amount = figure;
        }
        void setBaseSalary(const double& bSalary) { base_salary = bSalary; }
        void setBonus(const double& figure) { bonus = figure; }

        bool viewSalary();
        bool insertSalary(int id) const;
        double increment(double, int);
        bool deleteSalary();
        bool updateSalary();
        static std::optional<Model::Salary> getSalary(const std::string&);

    private:

        int Sid{};
        double amount{};
        double base_salary{};
        double bonus{};
    };
}



#endif