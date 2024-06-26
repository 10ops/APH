
#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"

int main(int argc, char **argv)
{
    if (false)// make false to run unit-tests
    {
        // debug section
			std::cout << "debug section" << std::endl;
			Matrix matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
			Matrix minor = algebra::minor(matrix, 1, 2);
			algebra::show(minor);
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}
