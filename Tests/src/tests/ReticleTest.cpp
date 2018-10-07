#define DISPLAY_LEAKS_DETAILS 1

#include "gtest-utilities.h"
#include "models/Reticle.h"


class ReticleFixture : public ::testing::Test {
protected:
    const unsigned _x_MIN = Reticle::CrossHairsPx_Max;
    const unsigned _x_MAX = Graphics::ScreenWidth - Reticle::CrossHairsPx_Max;
    const unsigned _y_MIN = Reticle::CrossHairsPx_Max;
    const unsigned _y_MAX = Graphics::ScreenHeight - Reticle::CrossHairsPx_Max;
};

TEST_F(ReticleFixture, reticleTest_moveOutOfBounds) {
    run_leakCheckDisabled([this]() {
        Reticle ret(Point2(2,2), Color(255,255,255));
        ret.move(-5, -1);
        EXPECT_EQ(_x_MIN , ret.getCenter().getX()); 
        EXPECT_EQ(_y_MIN , ret.getCenter().getY());
    });    
}

TEST_F(ReticleFixture, reticleTest_moveOutOfBoundsFromTopLeftScreenCorner) {
    run_leakCheckDisabled([this]() {
        Reticle ret(Point2(_x_MIN, _y_MIN), Color(255,255,255));
        ret.move(0, -1);
        EXPECT_EQ(_x_MIN , ret.getCenter().getX()); 
        EXPECT_EQ(_y_MIN , ret.getCenter().getY());
    });    
    run_leakCheckDisabled([this]() {
        Reticle ret(Point2(_x_MIN, _y_MIN), Color(255,255,255));
        ret.move(-1, 0);
        EXPECT_EQ(_x_MIN , ret.getCenter().getX()); 
        EXPECT_EQ(_y_MIN , ret.getCenter().getY());
    }); 
}

void foo() {
    run_leakCheckDisabled([]() {});
}