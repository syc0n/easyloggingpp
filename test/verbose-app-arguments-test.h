#ifndef VMODULE_TESTS_H_
#define VMODULE_TESTS_H_
#include "test.h"

TEST(VerboseAppArgumentsTest, AppArgsLevel) {

    const char* c[10];
    c[0] = "myprog";
    c[1] = "--v=5";
    c[2] = "\0";
    el::Helpers::setArgs(2, c);
    EXPECT_TRUE(VLOG_IS_ON(1));
    EXPECT_TRUE(VLOG_IS_ON(2));
    EXPECT_TRUE(VLOG_IS_ON(3));
    EXPECT_TRUE(VLOG_IS_ON(4));
    EXPECT_TRUE(VLOG_IS_ON(5));
    EXPECT_FALSE(VLOG_IS_ON(6));
    EXPECT_FALSE(VLOG_IS_ON(8));
    EXPECT_FALSE(VLOG_IS_ON(9));

    c[0] = "myprog";
    c[1] = "--v=x"; // SHOULD BE ZERO NOW!
    c[2] = "\0";
    el::Helpers::setArgs(2, c);
    EXPECT_FALSE(VLOG_IS_ON(1));
    EXPECT_FALSE(VLOG_IS_ON(2));
    EXPECT_FALSE(VLOG_IS_ON(3));
    EXPECT_FALSE(VLOG_IS_ON(4));
    EXPECT_FALSE(VLOG_IS_ON(5));
    EXPECT_FALSE(VLOG_IS_ON(6));
    EXPECT_FALSE(VLOG_IS_ON(8));
    EXPECT_FALSE(VLOG_IS_ON(9));

    c[0] = "myprog";
    c[1] = "-v"; // Sets to max level (9)
    c[2] = "\0";
    el::Helpers::setArgs(2, c);
    EXPECT_TRUE(VLOG_IS_ON(1));
    EXPECT_TRUE(VLOG_IS_ON(2));
    EXPECT_TRUE(VLOG_IS_ON(3));
    EXPECT_TRUE(VLOG_IS_ON(4));
    EXPECT_TRUE(VLOG_IS_ON(5));
    EXPECT_TRUE(VLOG_IS_ON(6));
    EXPECT_TRUE(VLOG_IS_ON(8));
    EXPECT_TRUE(VLOG_IS_ON(9));

    c[0] = "myprog";
    c[1] = "--verbose"; // Sets to max level (9)
    c[2] = "\0";
    el::Helpers::setArgs(2, c);
    EXPECT_TRUE(VLOG_IS_ON(1));
    EXPECT_TRUE(VLOG_IS_ON(2));
    EXPECT_TRUE(VLOG_IS_ON(3));
    EXPECT_TRUE(VLOG_IS_ON(4));
    EXPECT_TRUE(VLOG_IS_ON(5));
    EXPECT_TRUE(VLOG_IS_ON(6));
    EXPECT_TRUE(VLOG_IS_ON(8));
    EXPECT_TRUE(VLOG_IS_ON(9));

    // ----------------------- UPPER CASE VERSION OF SAME TEST CASES -----------------
    c[0] = "myprog";
    c[1] = "--V=5";
    c[2] = "\0";
    el::Helpers::setArgs(2, c);
    EXPECT_TRUE(VLOG_IS_ON(1));
    EXPECT_TRUE(VLOG_IS_ON(2));
    EXPECT_TRUE(VLOG_IS_ON(3));
    EXPECT_TRUE(VLOG_IS_ON(4));
    EXPECT_TRUE(VLOG_IS_ON(5));
    EXPECT_FALSE(VLOG_IS_ON(6));
    EXPECT_FALSE(VLOG_IS_ON(8));
    EXPECT_FALSE(VLOG_IS_ON(9));

    c[0] = "myprog";
    c[1] = "--V=x"; // SHOULD BECOME ZERO!
    c[2] = "\0";
    el::Helpers::setArgs(2, c);
    EXPECT_FALSE(VLOG_IS_ON(1));
    EXPECT_FALSE(VLOG_IS_ON(2));
    EXPECT_FALSE(VLOG_IS_ON(3));
    EXPECT_FALSE(VLOG_IS_ON(4));
    EXPECT_FALSE(VLOG_IS_ON(5));
    EXPECT_FALSE(VLOG_IS_ON(6));
    EXPECT_FALSE(VLOG_IS_ON(8));
    EXPECT_FALSE(VLOG_IS_ON(9));

    c[0] = "myprog";
    c[1] = "-V"; // Sets to max level (9)
    c[2] = "\0";
    el::Helpers::setArgs(2, c);
    EXPECT_TRUE(VLOG_IS_ON(1));
    EXPECT_TRUE(VLOG_IS_ON(2));
    EXPECT_TRUE(VLOG_IS_ON(3));
    EXPECT_TRUE(VLOG_IS_ON(4));
    EXPECT_TRUE(VLOG_IS_ON(5));
    EXPECT_TRUE(VLOG_IS_ON(6));
    EXPECT_TRUE(VLOG_IS_ON(8));
    EXPECT_TRUE(VLOG_IS_ON(9));

    c[0] = "myprog";
    c[1] = "--VERBOSE"; // Sets to max level (9)
    c[2] = "\0";
    el::Helpers::setArgs(2, c);
    EXPECT_TRUE(VLOG_IS_ON(1));
    EXPECT_TRUE(VLOG_IS_ON(2));
    EXPECT_TRUE(VLOG_IS_ON(3));
    EXPECT_TRUE(VLOG_IS_ON(4));
    EXPECT_TRUE(VLOG_IS_ON(5));
    EXPECT_TRUE(VLOG_IS_ON(6));
    EXPECT_TRUE(VLOG_IS_ON(8));
    EXPECT_TRUE(VLOG_IS_ON(9));
}

TEST(VerboseAppArgumentsTest, AppArgsVModules) {

    const char* c[10];
    c[0] = "myprog";
    c[1] = "-vmodule=main*=3,easy.\?\?\?=1";
    c[2] = "\0";
    el::Helpers::setArgs(2, c);

    EXPECT_TRUE((ELPP->vRegistry()->allowed(2, "main.cpp", ELPP->flags())));
    EXPECT_TRUE((ELPP->vRegistry()->allowed(3, "main.h", ELPP->flags())));
    EXPECT_FALSE((ELPP->vRegistry()->allowed(4, "main.c", ELPP->flags())));
    EXPECT_FALSE((ELPP->vRegistry()->allowed(5, "main.cpp", ELPP->flags())));
    EXPECT_TRUE((ELPP->vRegistry()->allowed(2, "main.cxx", ELPP->flags())));
    EXPECT_TRUE((ELPP->vRegistry()->allowed(1, "main.cc", ELPP->flags())));
    EXPECT_TRUE((ELPP->vRegistry()->allowed(3, "main-file-for-prog.cc", ELPP->flags())));

    el::Helpers::removeFlag(el::LoggingFlag::AllowVerboseIfModuleNotSpecified);  // Check strictly

    EXPECT_FALSE((ELPP->vRegistry()->allowed(4, "tmain.cxx", ELPP->flags())));

    EXPECT_TRUE((ELPP->vRegistry()->allowed(1, "easy.cpp", ELPP->flags())));
    EXPECT_TRUE((ELPP->vRegistry()->allowed(1, "easy.cxx", ELPP->flags())));
    EXPECT_TRUE((ELPP->vRegistry()->allowed(1, "easy.hxx", ELPP->flags())));
    EXPECT_TRUE((ELPP->vRegistry()->allowed(1, "easy.hpp", ELPP->flags())));

    EXPECT_FALSE((ELPP->vRegistry()->allowed(2, "easy.cpp", ELPP->flags())));
    EXPECT_FALSE((ELPP->vRegistry()->allowed(2, "easy.cxx", ELPP->flags())));
    EXPECT_FALSE((ELPP->vRegistry()->allowed(2, "easy.hxx", ELPP->flags())));
    EXPECT_FALSE((ELPP->vRegistry()->allowed(2, "easy.hpp", ELPP->flags())));

    EXPECT_FALSE((ELPP->vRegistry()->allowed(1, "easy.cc", ELPP->flags())));
    EXPECT_FALSE((ELPP->vRegistry()->allowed(1, "easy.hh", ELPP->flags())));
    EXPECT_FALSE((ELPP->vRegistry()->allowed(1, "easy.h", ELPP->flags())));
    EXPECT_FALSE((ELPP->vRegistry()->allowed(1, "easy.c", ELPP->flags())));
}
#endif // VMODULE_TESTS_H_
