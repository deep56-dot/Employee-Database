#pragma once
#pragma once
#include "include/Model/Department.h"
#include "gtest/gtest.h"

class DepartmentFixture : public testing::Test {
protected:

	void SetUp() {
		// Uncomment for UpdateTest
	/*	std::stringstream input(" BackEnd Team");
		std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
		d3.setName();
		std::cin.rdbuf(originalCin);

		std::stringstream input1(" Manage the backend part"); 
		std::streambuf* originalCin1 = std::cin.rdbuf(input1.rdbuf());
		d3.setDescription();
		std::cin.rdbuf(originalCin1);

		d3.setManagerId(2);*/


		//Uncomment for DeleteTest
	/*	std::stringstream input(" BackZEnd"); 
		std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf()); 
		d3.setName();  
		std::cin.rdbuf(originalCin);

		std::stringstream input1(" HR");
		std::streambuf* originalCin1 = std::cin.rdbuf(input1.rdbuf());
		d4.setName();
		std::cin.rdbuf(originalCin1);*/

	}

	void TearDown() {

	}

	Department d1{ 1 , "Finance" , 1 , "Do the work related to money " };
	Department d2{ 3 , "Finance" , 5 , "Do the work related to money " };
	Department d3{ 3 , "Web Dev" , 1 , "Do the work related to Website Handling" };
	Department d4{ 4 , "HR" , 1 , "Do the work related to Human resource and management of employees" };
	Department d5{ 5 , "QA" , 1 , "Do the work related to Human resource and management of employees" };
	Department d6 = d4;
};