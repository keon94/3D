#include <gtest/gtest.h>
#include <vld.h>

//Enables leak information to be output to the console
#ifndef DISPLAY_LEAKS_DETAILS
    #define DISPLAY_LEAKS_DETAILS 0
#endif

/**
* \brief runs \ref f with arguments \ref args and checks for leaks
*/
template <typename F, typename ... Args>
void run_leakCheckEnabled(F&& f, Args&& ... args) {
    unsigned leaks = VLDGetLeaksCount();
    VLDGlobalEnable();
    f(args...);
    leaks = VLDGetLeaksCount() - leaks;
    run_leakCheckDisabled([&]() {EXPECT_EQ(leaks, 0);});
    #if DISPLAY_LEAKS_DETAILS
        VLDReportLeaks();
    #else
        VLDMarkAllLeaksAsReported();
    #endif
}

/**
* \brief runs \ref f with arguments \ref args and disables leak checks meanwhile
*/
template <typename F, typename ... Args>
void run_leakCheckDisabled(F&& f, Args&& ... args) {
    VLDGlobalDisable();
    f(args...);
    VLDRestore();
}
