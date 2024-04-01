#pragma once
#include "include/Model/Department.h"
#include "include/controllers/departmentController.h"
#include "gtest/gtest.h"

class DepartmentFixture : public testing::Test {
	protected:

		void SetUp() {
			d2.setManagerId(10);
				
			d3.setName("For testing");
			
		}

		void TearDown() {

		}

		Model::Department d1{1 , "Finance" , 2 , "Do the work related to money "};
		Model::Department d2{3 , "Finance" , 5 , "Do the work related to money "};
		Model::Department d3{3 , "Web Dev" , 2 , "Do the work related to Website Handling"};
		Model::Department d4{4 , "HR" , 2 , "Do the work related to Human resource and management of employees"};
		Model::Department d5{5 , "HR" , 1 , "Do the work related to Human resource and management of employees"};
		Model::Department d6 = d4;
};