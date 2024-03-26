#pragma once
#pragma once
#include "include/Model/Manager.h"
#include "gtest/gtest.h"

class ManagerFixture : public testing::Test {
protected:
	void SetUp() {
		m4.setId(504);
		m5.setId(505);

		//Un Comment for InsertTest
		//m6.setDepartmentId(3);
		//m7.setManagerId(506);

		//Un Comment for UpdateTest
		//m6.setManagerId(506);
		//m7.setDepartmentId(5);
		//m8.setId(507);
		//m1.setDob("26-08-2003");
		//m1.setEmail("Deep@gmail.com");
		//m1.setManagerId(503);


		//Uncomment for DeleteTest
		m9.setId(510);
		m2.setEmail("this2@gmail.com");
		m4.setId(504);
		m5.setEmail("test1@gmail.com");
	}
	void TearDown() {

	}
	Salary s{ 1,600000,500000,100000 };
	Manager m1{ 1,"Deep","Dhuvad","26-08-2002","1234567890","efgsd@hjfsgb.jsfdh","Surat",Gender::Male,"01-01-2024",1,2,s,2,"DBM" };
	Manager m2{ 502,"Zeal","shah","12-08-2004","1234567890","test@gmail.com","Ahmedabad",Gender::Male,"01-06-2024",1,2,s,2,"DBM" };
	Manager m3{ 503,"deep","dhuvad","16-08-2003","1234567890","test@zuru.com","Himatnagar",Gender::Male,"01-01-2024",1,2,s,2,"DBM" };
	Manager m4 = m2;
	Manager m5 = m2;
	Manager m6 = m2;
	Manager m7 = m2;
	Manager m8 = m2;
	Manager m9 = m2;





};