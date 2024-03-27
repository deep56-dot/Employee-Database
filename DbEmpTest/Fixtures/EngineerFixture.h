
#pragma once
#include "include/Model/Engineer.h"
#include "include/Model/Salary.h"
#include "gtest/gtest.h"
using Model::Engineer,Model::Salary;
class EngineerFixture : public testing::Test {
protected:

	void SetUp() {
		eng.setId(1);
		eng.setFirstname("Deep");
		eng.setLastname("Dhuvad");
		eng.setDob("16-08-2003");
		eng.setEmail("deep@gmail.com");
		eng.setMobile("2542345671");
		eng.setGender(Gender::Male);
		eng.setDoj("01-01-2024");
		eng.setManagerId(1);
		eng.setDepartmentId(1);

		std::stringstream input(" Hmt Gujarat");
		std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
		eng.setAddress();
		std::cin.rdbuf(originalCin);

		eng.setProgramming_language("JAVA");

		std::stringstream input1(" Jr Software Engineer");
		std::streambuf* originalCin1 = std::cin.rdbuf(input.rdbuf());
		eng.setSpecialization();
		std::cin.rdbuf(originalCin);


		eg3.setDepartmentId(5);
		eg3.setManagerId(1);


		// Uncomment for UpdateTest
	/*	eg2.setId(1);
		eg1.setId(1);
		eg1.setDepartmentId(5);
		eng.setDob("26-08-2003");
		eng.setEmail("newemail@gmail.com");
		eng.setManagerId(1);
		eng.setDepartmentId(1);*/



		// Uncomment for DeleteTest
		eg3.setId(1);
		eg3.setEmail("dfhja@djhfg.fedjb");
		eg2.setId(2); 
		eg1.setEmail("this@gmail.com");
	}

	void TearDown() {

	}
	Salary sg1{ 4 , 600000.0 , 500000.0 , 100000.0 };
	Engineer eng;
	Engineer eg1{ 3 , "Kalpesh" , "Shukla" , "16-12-1212" , "5567894565" , "this@gmail.com" , "jsdhgfd fgsd" , Gender::Male , "01-01-2023" , 1 , 1 , sg1 , "C++", "Senior C++ Develpoer" };
	Engineer eg2{ 4 , "Kalpesh" , "Shukla" , "16-12-1212" , "5567894565" , "this@gmail.com" , "jsdhgfd fgsd" , Gender::Male , "01-01-2023" , 15 , 1 , sg1 , "C++", "Senior C++ Develpoer" };
	Engineer eg4{ 4 , "Kalpesh" , "Shukla" , "16-12-1212" , "5567894565" , "this@gmail.com" , "jsdhgfd fgsd" , Gender::Male , "01-01-2023" , 15 , 1 , sg1 , "C++", "Senior C++ Develpoer" };
	Engineer eg3 = eg2;


};