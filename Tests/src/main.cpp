#include <gmock/gmock.h>
#include <vld.h>

int main(int argc, char** argv) {
    VLDGlobalDisable();
    ::testing::InitGoogleMock(&argc,argv);
    VLDMarkAllLeaksAsReported();
    RUN_ALL_TESTS();
    VLDMarkAllLeaksAsReported();
}