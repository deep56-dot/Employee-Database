#ifndef _EmpView_
#define _EmpView_
#include"../Model/Employee.h"
#include "SalaryView.h"

std::optional<Model::Employee> userInputEmployee(); 
std::optional<std::pair<string, string>> viewEmp();
std::optional<Model::Employee> updateEmpViewer();
#endif
