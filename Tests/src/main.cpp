#include <gmock/gmock.h>
#include <vld.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    std::atexit([](){std::cin.get();});
    VLDGlobalDisable();
    ::testing::InitGoogleMock(&argc,argv);
    VLDMarkAllLeaksAsReported();
    RUN_ALL_TESTS();
    VLDMarkAllLeaksAsReported();    
}