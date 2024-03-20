#pragma once
# include "pch.h"
#include "gtest/gtest.h"
#include "include/DBmanage.h"
#include "include/Model/Employee.h"
class EmployeeFixture : public testing::Test {
protected:
	void SetUp() override{
        employee.setId(101);
        employee.setFirstname("John");
        employee.setLastname("Doe");
        employee.setDob("1990-05-20");
        employee.setMobile("1234567890");
        employee.setEmail("john.doe@example.com");
        //employee.setAddress();
        employee.setGender(Gender::Male); 
        employee.setDoj("2020-01-15");
        employee.setManagerId(1001);
        employee.setDepartmentId(500);
	}
	Employee employee;

};