#pragma once
#include "include/Model/Engineer.h"
#include "include/Model/Salary.h"
#include "gtest/gtest.h"

class EngineerFixture : public testing::Test {
protected:

	void SetUp() {
		eng.setId(301);
		eng.setFirstname("Deep");
		eng.setLastname("Dhuvad");
		eng.setDob("16-08-2003");
		eng.setEmail("deep@gmail.com");
		eng.setMobile("1234567890");
		eng.setGender(Gender::Male);
		eng.setDoj("01-01-2024");
		eng.setManagerId(2);
		eng.setDepartmentId(1);
		eng.setAddress("Himatnagar Gujarat");
		eng.setProgramming_language("C++");
		eng.setSpecialization("Jr Software Engineer");

		eg4.setManagerId(10);
		eg5.setDepartmentId(10);
		eg6.setId(310);

	}

	void TearDown() {

	}	
	Model::Salary sg1{ 4 , 600000.0 , 500000.0 , 100000.0 };
	Model::Engineer eng;
	Model::Engineer eg1{ 301 , "Kalpesh" , "Shukla" , "16-12-1212" , "5567894565" , "this@gmail.com" , "jsdhgfd fgsd" , Gender::Male , "01-01-2023" , 2 , 1 , sg1 , "C++", "Senior C++ Develpoer" };
	Model::Engineer eg2{ 301 , "Kalpesh" , "Shukla" , "16-12-1212" , "5567894565" , "this@gmail.com" , "jsdhgfd fgsd" , Gender::Male , "01-01-2023" , 15 , 1 , sg1 , "C++", "Senior C++ Develpoer" }; 
	Model::Engineer eg3{ 305 , "Kalpesh" , "Shukla" , "16-12-1212" , "5567894565" , "this@gmail.com" , "jsdhgfd fgsd" , Gender::Male , "01-01-2023" , 2 , 5 , sg1 , "C++", "Senior C++ Develpoer" };
	Model::Engineer eg4 = eg1;
	Model::Engineer eg5 = eg1;
	Model::Engineer eg6 = eg1;
	

};