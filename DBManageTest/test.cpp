#include "pch.h"
//#include "include/helper.h"
#include "include/DBmanage.h"
#include "EmployeeFixture.h"
//TEST(TestCaseName, TestName) {
//	EXPECT_EQ(Database::getInstance().open("Emp.db"), true)<<"2";
//	EXPECT_EQ(Database::getInstance().selectQuery("select * from Deep"), true)<<"1";
//}

TEST_F(EmployeeFixture, AllGetters) {
    ASSERT_EQ(employee.getId(), 101);
    ASSERT_EQ(employee.getFirstname(), "John");
    ASSERT_EQ(employee.getLastname(), "Doe");
    ASSERT_EQ(employee.getDob(), "1990-05-20");
    ASSERT_EQ(employee.getMobile(), "1234567890");
    ASSERT_EQ(employee.getEmail(), "john.doe@example.com");
    //ASSERT_EQ(employee.getAddress(), "123 Main St");
    ASSERT_EQ(employee.getGender(), Gender::Male);
    ASSERT_EQ(employee.getDoj(), "2020-01-15");
    ASSERT_EQ(employee.getManagerId(), 1001);
    ASSERT_EQ(employee.getDepartmentId(), 500);
}

TEST_F(EmployeeFixture, CRUD) {
    //ASSERT_TRUE(employee.insertEmployee());
    ASSERT_TRUE(employee.deleteEmployee());
    ASSERT_TRUE(employee.updateEmployee());
    ASSERT_TRUE(employee.viewEmployee());

}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}