#include "SalaryView.h"
std::optional<Model::Salary> userInputSalary() {

	try {
		Model::Salary s;
		std::string msg = " Enter # to leave the field Empty: \n";

		if (auto tmp = input("Enter Base Salary OR " + msg, salaryRegex, true); tmp.has_value()) s.setBaseSalary(std::stof(tmp.value()));
		else return std::nullopt;

		if (auto tmp = input("Enter Bonus OR " + msg, salaryRegex, true); tmp.has_value()) s.setBonus(std::stof(tmp.value()));
		else return std::nullopt;

		s.setAmount(s.getBaseSalary() + s.getBonus());
		return s;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		waitMenu();
		return std::nullopt;
	}
}