
#include "StdAfx.h"

#include <AzTest/AzTest.h>

class TutorialSeriesTest
    : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TutorialSeriesTest, ExampleTest)
{
    ASSERT_TRUE(true);
}

AZ_UNIT_TEST_HOOK();
