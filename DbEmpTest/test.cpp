#include "pch.h"
#include "include/Model/Employee.h"
#include "Fixtures/EmployeeFixture.h"
#include "Fixtures/EngineerFixture.h"
#include "Fixtures/DepartmentFixture.h"
#include "Fixtures/ManagerFixture.h"
#include "Fixtures/SalaryFixture.h"


//TEST(TestCaseName, TestName) {    
//  EXPECT_EQ(1, 1);
//  ASSERT_EQ(fun(), "Deep");
//}
//
//TEST_F(EmployeeFixture , constructionTest) {  
//	ASSERT_EQ(emp.getId(), 1);
//	ASSERT_EQ(emp.getFirstname(), "Deep");
//	ASSERT_EQ(emp.getLastname(), "Dhuvad");
//	ASSERT_EQ(emp.getEmail(), "Deep@gmail.com");
//	ASSERT_EQ(emp.getMobile(), "8469557424");
//	ASSERT_EQ(emp.getDob(), "26-08-2002"); 
//	ASSERT_EQ(emp.getDoj(), "01-01-2024"); 
//	ASSERT_EQ(emp.getManagerId(), 1); 
//	ASSERT_EQ(emp.getDepartmentId(), 1); 
//	ASSERT_EQ(emp.getGender(), Gender::Male);
//}

// Employee 

TEST_F(EmployeeFixture, DISABLED_ViewTest) {
	ASSERT_TRUE(emp.viewEmployee()); //sucess
	ASSERT_FALSE(emp.viewEmployee()); //record not avilable     
}

TEST_F(EmployeeFixture, DISABLED_InsertTest) {
	ASSERT_TRUE(e1.insertEmployee());  // Success
	ASSERT_FALSE(e2.insertEmployee());  // Fail because Employee is already exist 
	ASSERT_FALSE(e3.insertEmployee()); // Fail Beacause Manager is not available 
	ASSERT_FALSE(e4.insertEmployee()); // Fail Beacause Department is not available 
}

TEST_F(EmployeeFixture, DISABLED_UpdateTest) {
	ASSERT_FALSE(emp.updateEmployee()); //  updated manager id is not available 
	EXPECT_FALSE(emp.updateEmployee()); // Updated Department id is not avialable 
	EXPECT_FALSE(e3.updateEmployee()); // Enter Employee is not aviable  
	ASSERT_TRUE(e1.updateEmployee()); // Sucess     
}

TEST_F(EmployeeFixture, DISABLED_DeleteTest) {
	ASSERT_FALSE(emp.deleteEmployee()); // Fail Beacuse  it is a manager of other employeees  
	ASSERT_FALSE(e4.deleteEmployee()); // Fail because Employee with given id is not available  
	ASSERT_FALSE(e2.deleteEmployee()); // Fail because Employee with given Email is not available  

	ASSERT_TRUE(e3.deleteEmployee());  // Suceess   
	ASSERT_TRUE(e1.deleteEmployee());  // Suceess    
}

// Engineer 

TEST_F(EngineerFixture, DISABLED_InsertTest) {
	ASSERT_TRUE(eg1.insertEngineer());    // Success  
	ASSERT_FALSE(eng.insertEngineer());  // Fail because Employee is already exist  
	ASSERT_FALSE(eg2.insertEngineer()); // Fail Beacause Manager is not available  
	ASSERT_FALSE(eg3.insertEngineer()); // Fail Beacause Department is not available  
}

TEST_F(EngineerFixture, DISABLED_ViewTest) {
	ASSERT_TRUE(eg1.viewEngineer()); //sucess 
	ASSERT_FALSE(eng.viewEngineer()); //record not avilable   
}

TEST_F(EngineerFixture, DISABLED_UpdateTest) {
	ASSERT_FALSE(eg2.updateEngineer()); //  updated manager id is not available  
	EXPECT_FALSE(eg1.updateEngineer()); // Updated Department id is not avialable    
	EXPECT_FALSE(eg4.updateEngineer()); // Enter Employee is not aviable      
	ASSERT_TRUE(eng.updateEngineer()); // Sucess         
}

TEST_F(EngineerFixture, DISABLED_DeleteTest) {
	ASSERT_FALSE(eng.deleteEngineer()); // Fail Beacuse  it is a manager of other employeees    
	ASSERT_FALSE(eg4.deleteEngineer()); // Fail because Employee with given id is not available    
	ASSERT_FALSE(eg3.deleteEngineer()); // Fail because Employee with given Email is not available    

	ASSERT_TRUE(eg2.deleteEngineer());  // Suceess  ID    
	ASSERT_TRUE(eg1.deleteEngineer());  // Sucess   Email   
}

// Department 
TEST_F(DepartmentFixture, DISABLED_InsertTest) {
	ASSERT_FALSE(d1.insertDepartment()); // Fail because With given department id there is already some other department 
	ASSERT_FALSE(d2.insertDepartment());  // Fail because enterd manager is not in manager table  
	ASSERT_TRUE(d3.insertDepartment()); // Success 
	ASSERT_TRUE(d4.insertDepartment()); // Success
}

TEST_F(DepartmentFixture, DISABLED_ViewTest) {
	ASSERT_FALSE(d1.viewDepartment());
}

TEST_F(DepartmentFixture, DISABLED_UpdateTest) {
	ASSERT_FALSE(d2.updateDepartment());  // Fail because manager id is not in database
	ASSERT_FALSE(d5.updateDepartment()); // Fali beacuse department is not in table 
	ASSERT_TRUE(d3.updateDepartment());  // Success
}

TEST_F(DepartmentFixture, DISABLED_DeleteTest) {
	ASSERT_FALSE(d1.deleteDepartment()); // Fail because there is employee which are working in this department 
	ASSERT_FALSE(d5.deleteDepartment()); // Fail beacuse there is no department like this id 
	ASSERT_FALSE(d5.deleteDepartment()); // Fail beacuse there is no department like this name 

	ASSERT_TRUE(d3.deleteDepartment());  // Success id
	ASSERT_TRUE(d4.deleteDepartment());  // Success name
}

// Manager 
TEST_F(ManagerFixture, DISABLED_InsertTest) {
	ASSERT_TRUE(m2.insertManager());    // Success  
	ASSERT_TRUE(m3.insertManager());    // Success  
	ASSERT_TRUE(m4.insertManager());    // Success  
	ASSERT_TRUE(m5.insertManager());    // Success  

	ASSERT_FALSE(m1.insertManager());  // Fail because Employee is already exist    
	ASSERT_FALSE(m6.insertManager()); // Fail Beacause Department is not available  
	ASSERT_FALSE(m7.insertManager()); // Fail Beacause Manager is not available  
}

TEST_F(ManagerFixture, DISABLED_UpdateTest) {
	ASSERT_FALSE(m6.updateManager()); //  updated manager id is not available  
	EXPECT_FALSE(m7.updateManager()); // Updated Department id is not avialable    
	EXPECT_FALSE(m8.updateManager()); // Enter Employee is not aviable      
	ASSERT_TRUE(m1.updateManager()); // Sucess
}

TEST_F(ManagerFixture, DISABLED_ViewTest) {
	EXPECT_TRUE(m1.viewManager());
}
TEST_F(ManagerFixture, DISABLED_DelelteTest) {
	ASSERT_FALSE(m1.deleteManager()); // Fail beacuse this is a manager of other emloyees 
	ASSERT_FALSE(m9.deleteManager()); // Fail becuse such manager is not available 
	ASSERT_FALSE(m2.deleteManager()); // Fail beacuse manager with this email is not exist

	ASSERT_TRUE(m4.deleteManager()); // Success ID
	ASSERT_TRUE(m5.deleteManager()); // Success Email

}

// Salary
TEST_F(SalaryFixture, DISABLED_IncrementTest) {
	double d1 = s1.getBaseSalary();
	s1.increment(25, s1.getId());

	double d2 = d1 + (d1 * 0.25);
	ASSERT_DOUBLE_EQ(s1.getBaseSalary(), d2);
	ASSERT_DOUBLE_EQ(s1.getAmount(), s1.getBaseSalary() + s1.getBonus());
}

TEST_F(SalaryFixture, DISABLED_ViewTest) {
	ASSERT_TRUE(s1.viewSalary());
}

TEST_F(SalaryFixture, DISABLED_UpdateTest) {
	ASSERT_FALSE(s3.updateSalary()); // Fail beacuse Sid is not in table
	s2.updateSalary();
	ASSERT_DOUBLE_EQ(s2.getAmount(), s2.getBaseSalary() + s2.getBonus()); // Success base_salary  
	s4.updateSalary();
	ASSERT_DOUBLE_EQ(s4.getAmount(), s4.getBaseSalary() + s4.getBonus()); // Success bonus 
}

int main(int argv, char** argc) {
	Database::getInstance().open("Emp.db");
	testing::InitGoogleTest(&argv, argc);
	return RUN_ALL_TESTS();
}