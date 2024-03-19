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

    void viewSalary();
    void userInputSalary();
    void insertSalary(int id) const;
    void increment(double, std::string);
    void deleteSalary();
    void updateSalary();
    void action() noexcept;

private:

    int Sid;
    double amount{};
    double base_salary{};
    double bonus{};
};

#endif