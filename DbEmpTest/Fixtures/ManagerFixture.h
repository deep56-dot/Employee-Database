#pragma once
#include "include/Model/Manager.h"
#include "gtest/gtest.h"

class ManagerFixture : public testing::Test {
protected:
	void SetUp() {

		m6.setDepartmentId(10);
		m7.setManagerId(10);
		m8.setId(510);

		m9.setDob("01-01-2000");
		m9.setGender(Gender::Other);

		m10.setId(510);
		m11.setId(511);

	}

	void TearDown() {

	}

	Model::Salary s{ 1,600000,500000,100000 };
	Model::Manager m1{ 2,"darshan","chandegara","26-08-2002","1234567890","efgsd@hjfsgb.jsfdh","Surat",Gender::Male,"01-01-2024",1,2,s,2,"DBM" };
	Model::Manager m2{ 501,"Zeal","shah","12-08-2004","1234567890","test@gmail.com","Ahmedabad",Gender::Male,"01-06-2024",2,1,s,2,"DBM" };
	Model::Manager m3{ 502,"deep","dhuvad","16-08-2003","1234567890","test@zuru.com","Himatnagar",Gender::Male,"01-01-2024",2,1,s,2,"DBM" };
	Model::Manager m4 = m2;
	Model::Manager m5 = m2;
	Model::Manager m6 = m2;
	Model::Manager m7 = m2;
	Model::Manager m8 = m2;
	Model::Manager m9 = m2;
	Model::Manager m10 = m2;
	Model::Manager m11 = m2;


	


};