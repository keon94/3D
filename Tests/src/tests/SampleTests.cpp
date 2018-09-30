#include <vld.h>

#define DISPLAY_LEAKS_DETAILS 1

#include "gtest-utilities.h"

class SampleFixture : public testing::Test {
};

TEST_F(SampleFixture, sampleTest_leakCheck) {
    run_leakCheckEnabled([]() {
        int x = 0;
        run_leakCheckDisabled([&]() { EXPECT_EQ(0, x); });
        int* y = new int(1);
        run_leakCheckDisabled([&]() { EXPECT_EQ(1, *y); });
        delete y;
    });    
}


TEST_F(SampleFixture, sampleTest_noLeakCheck) {
    run_leakCheckDisabled([]() {
        int x = 0;
        run_leakCheckDisabled([&]() { EXPECT_EQ(0, x); });
        int* y = new int(1);
        run_leakCheckDisabled([&]() { EXPECT_EQ(1, *y); });
    });  
}
