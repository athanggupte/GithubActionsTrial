#include <Asserts.h>
#include <gtest/gtest.h>

TEST(AssertsDeathTest, AssertAborts)
{
	ASSERT_DEATH(APEX_ASSERT(1 == 0, "This should fail"), "");
}

//TEST(AssertsTest, ExecutionContext)
//{
//	
//}
