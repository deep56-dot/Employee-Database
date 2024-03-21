#include "pch.h"
#include "include/Model/Employee.h"
#include "Fixtures/EmployeeFixture.h"
#include "Fixtures/EngineerFixture.h"


//TEST(TestCaseName, TestName) {    
//  EXPECT_EQ(1, 1);
//  ASSERT_EQ(fun(), "darshan");
//}
//
//TEST_F(EmployeeFixture , constructionTest) {  
//	ASSERT_EQ(emp.getId(), 1);
//	ASSERT_EQ(emp.getFirstname(), "Darshan");
//	ASSERT_EQ(emp.getLastname(), "Chandegara");
//	ASSERT_EQ(emp.getEmail(), "darshan@gmail.com");
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

TEST_F(EngineerFixture, DeleteTest) {
	ASSERT_FALSE(eng.deleteEngineer()); // Fail Beacuse  it is a manager of other employeees    
	ASSERT_FALSE(eg4.deleteEngineer()); // Fail because Employee with given id is not available    
	ASSERT_FALSE(eg3.deleteEngineer()); // Fail because Employee with given Email is not available    

	ASSERT_TRUE(eg2.deleteEngineer());  // Suceess  ID    
	ASSERT_TRUE(eg1.deleteEngineer());  // Sucess   Email   
}



int main(int argv, char** argc) {
	Database::getInstance().open("Emp.db");
	testing::InitGoogleTest(&argv, argc);
	return RUN_ALL_TESTS();
}