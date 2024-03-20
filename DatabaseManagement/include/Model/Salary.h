#ifndef _Salary_
#define _Salary_
#include <iostream> 
#include <map> 
#include "../Helper.h"
#include "../Regex.h"
#include "../DBmanage.h"

class Salary {
public:

    Salary() = default;
    Salary(int id, int emp_id, double amount, double base_salary, double bonus)
        : Sid(id), amount(amount), base_salary(base_salary), bonus(bonus) {}

    int getId() const { return Sid; }
    double getAmount() const { return amount; }
    double getBaseSalary() const { return base_salary; }
    double getBonus() const { return bonus; }

    void setAmount(double figure) {
        amount = figure;
    }
    void setBaseSalary(const double& bSalary) { base_salary = bSalary; }
    void setBonus(const double& figure) { bonus = figure; }

    bool viewSalary();
    void userInputSalary();
    bool insertSalary(int id) const;
    double increment(double, std::string);
    bool deleteSalary();
    bool updateSalary();
    void action() noexcept;

private:

    int Sid;
    double amount{};
    double base_salary{};
    double bonus{};
};

#endif