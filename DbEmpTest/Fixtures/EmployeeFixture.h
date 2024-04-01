#pragma once
#include "include/Model/Employee.h"
#include "include/Model/Salary.h"
#include "include/controllers/employeeController.h"
#include "gtest/gtest.h"

class EmployeeFixture : public testing::Test {
protected:

	void SetUp() {
		emp.setId(1);
		emp.setFirstname("Deep");
		emp.setLastname("Dhuvad");
		emp.setDob("16-08-2003");
		emp.setEmail("deep@gmail.com");
		emp.setMobile("1234567890");
		emp.setGender(Gender::Male);
		emp.setDoj("01-01-2024");
		emp.setManagerId(1);
		emp.setDepartmentId(1);	

		e3.setManagerId(15);
		e4.setDepartmentId(15);
		e5.setId(4);

		e6.setManagerId(15);
		e7.setDepartmentId(15);
		e8.setId(10);
		e1.setDob("01-01-1999");
		e1.setEmail("this@gmail.com");

		e9.setId(2);
	}

	void TearDown() {

	}
	Model::Salary s{ 2 , 600000.0 , 500000.0 , 100000.0 };
	Model::Employee emp;
	Model::Employee e1{ 3 , "darshan" , "patel" , "16-12-1212" , "5567894565" , "this@gmail.com" , "jsdhgfd fgsd" , Gender::Male , "01-01-2023" , 2 , 1 , s};
	Model::Employee e2 = e1;
	Model::Employee e3 = e1;
	Model::Employee e4 = e1;
	Model::Employee e5 = e1;
	Model::Employee e6 = e1;
	Model::Employee e7 = e1;
	Model::Employee e8 = e1; 
	Model::Employee e9 = e1; 
};