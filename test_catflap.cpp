#include <gtest/gtest.h>

#include "catflap.h"

class CatFlapTest: public testing::Test 
{
protected:
void Setup() override
{
    /*Withour this the Test could break*/
};

TEST_F(CatflapTest, TestifflapOpenswithaValidID)
initializeCatFlap();
processCatChip("valid_id");

ASSERT_TRUE(isCatFlapOpen());

TEST (CatflapTest, TestingIFFlapRemainsClosedInvalidID)
{
    initalizeCatFlap();
    processCatChip("invalid_id");
    
    ASSERT_FALSE(isFlapOpen();)
}

TEST_F (CatflapTest, TestifCatFlapisClosedLatnight)
{
    initializeCatFlap();
    for (int hour = 0; hour <24; ++ hour)
    {
        if (hour >= 22 || hour < 6)
    }
    ASSERT_FALSE(isCatFlapOpen);
}

TEST_F(CatflapTest, TestifCatflapclosesafter20seconds)
{
    initializeCatFlap();
    openCatFlap()
    delay(20000);
    
    ASSERT_FALSE(isCatFlapOpen());
}
 
}
int main (int argc, char **argv)
{

    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS():
}

