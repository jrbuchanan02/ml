/**
 * @file unittest.cc
 * @author Joshua Buchanan (joshuarobertbuchanan@gmail.com)
 * @brief Entry point for unittesting.
 * @version 1
 * @date 2022-04-13
 *
 * @copyright Copyright (C) 2022. Intellectual property of the author(s) listed
 * above.
 *
 */
#include "math/matrix.hh"

#include <iostream>

void testVectorMultiplication ( );

void testMatrixMultiplication ( );

void echelonTest ( );

void inverseTest ( );

int main ( int const, char const *const *const )
{
    std::cout << "Compiled for " << __cplusplus << "\n";
    testVectorMultiplication ( );
    testMatrixMultiplication ( );
    echelonTest ( );

    inverseTest ( );
}

void inverseTest ( )
{
    using namespace ml;
    Matrix< Double > test { 3, 3 };
    test [ 0 ] = std::vector< Double > { 1, 2, 3 };
    test [ 1 ] = std::vector< Double > { 4, 5, 6 };
    test [ 2 ] = std::vector< Double > { 7, 8, 8 };
    std::cout << "Expected: [" << -8.0 / 3 << "," << 8.0 / 3 << "," << -1.0
              << ";";
    std::cout << 10.0 / 3 << "," << -13.0 / 3 << "," << 2.0 << ";";
    std::cout << -1.0 << "," << 2 << ","
              << "-1]\n";
    auto result = test.inverse ( );
    std::cout << "Actual:   [";
    std::cout << result [ 0 ][ 0 ] << "," << result [ 0 ][ 1 ] << ","
              << result [ 0 ][ 2 ] << ";";
    std::cout << result [ 1 ][ 0 ] << "," << result [ 1 ][ 1 ] << ","
              << result [ 1 ][ 2 ] << ";";
    std::cout << result [ 2 ][ 0 ] << "," << result [ 2 ][ 1 ] << ","
              << result [ 2 ][ 2 ] << "]\n";

    std::cout << "Does this result pass?";
    bool passes = ( result * test ) == Matrix< Double >::identity ( 3 )
               || ( test * result ) == Matrix< Double >::identity ( 3 );
    std::cout << ( passes ? " Yes" : " No" ) << "\n";

    std::cout << "Product of test and its supposed inverse:\n";
    auto product = result * test;
    std::cout << product [ 0 ][ 0 ] << " " << product [ 0 ][ 1 ] << " "
              << product [ 0 ][ 2 ] << "\n";
    std::cout << product [ 1 ][ 0 ] << " " << product [ 1 ][ 1 ] << " "
              << product [ 1 ][ 2 ] << "\n";
    std::cout << product [ 2 ][ 0 ] << " " << product [ 2 ][ 1 ] << " "
              << product [ 2 ][ 2 ] << "\n";
    std::cout << "Reversed:\n";
    product = test * result;
    std::cout << product [ 0 ][ 0 ] << " " << product [ 0 ][ 1 ] << " "
              << product [ 0 ][ 2 ] << "\n";
    std::cout << product [ 1 ][ 0 ] << " " << product [ 1 ][ 1 ] << " "
              << product [ 1 ][ 2 ] << "\n";
    std::cout << product [ 2 ][ 0 ] << " " << product [ 2 ][ 1 ] << " "
              << product [ 2 ][ 2 ] << "\n";
}

void echelonTest ( )
{
    using namespace ml;
    Matrix< Double > test { 2, 2 };
    test [ 0 ] = std::vector< Double > { 1, 2 };
    test [ 1 ] = std::vector< Double > { 3, 4 };

    std::cout << "Expected: [1,0;0,1] or equivalent\n";
    std::cout << "Actual: ";
    auto result = test.echelon ( );
    std::cout << "[" << result [ 0 ][ 0 ] << "," << result [ 0 ][ 1 ] << ";"
              << result [ 1 ][ 0 ] << "," << result [ 1 ][ 1 ] << "]\n";

    test [ 1 ] = std::vector< Double > { 1, 2 };

    std::cout << "Expected: [1,2;0,0]\n";
    std::cout << "Actual: ";
    result = test.echelon ( );
    std::cout << "[" << result [ 0 ][ 0 ] << "," << result [ 0 ][ 1 ] << ";"
              << result [ 1 ][ 0 ] << "," << result [ 1 ][ 1 ] << "]\n";

    test       = Matrix< Double > { 3, 3 };
    test [ 0 ] = std::vector< Double > { 1, 2, 3 };
    test [ 1 ] = std::vector< Double > { 4, 5, 6 };
    test [ 2 ] = std::vector< Double > { 7, 8, 9 };

    std::cout << "Expected: [1,0,-1;0,1,2;0,0,0]\n";
    std::cout << "Actual:   ";
    result = test.echelon ( );
    std::cout << "[";
    std::cout << result [ 0 ][ 0 ] << "," << result [ 0 ][ 1 ] << ","
              << result [ 0 ][ 2 ] << ";";
    std::cout << result [ 1 ][ 0 ] << "," << result [ 1 ][ 1 ] << ","
              << result [ 1 ][ 2 ] << ";";
    std::cout << result [ 2 ][ 0 ] << "," << result [ 2 ][ 1 ] << ","
              << result [ 2 ][ 2 ] << "]\n";

    test       = Matrix< Double > { 3, 4 };
    test [ 0 ] = std::vector< Double > { 1, 2, 3, 4 };
    test [ 1 ] = std::vector< Double > { 5, 6, 7, 8 };
    test [ 2 ] = std::vector< Double > { 9, 10, 11, 12 };
    result     = test.echelon ( );
    std::cout << "Expected: [1,0,-1,-2;0,1,2,3;0,0,0,0]\n";
    std::cout << "Actual:   [";
    std::cout << result [ 0 ][ 0 ] << "," << result [ 0 ][ 1 ] << ","
              << result [ 0 ][ 2 ] << "," << result [ 0 ][ 3 ] << ";";
    std::cout << result [ 1 ][ 0 ] << "," << result [ 1 ][ 1 ] << ","
              << result [ 1 ][ 2 ] << "," << result [ 1 ][ 3 ] << ";";
    std::cout << result [ 2 ][ 0 ] << "," << result [ 2 ][ 1 ] << ","
              << result [ 2 ][ 2 ] << "," << result [ 2 ][ 3 ] << "]\n";
}

void testMatrixMultiplication ( )
{
    using namespace ml;

    Matrix< Double >      lhs { 3, 3 };
    Matrix< Triple > rhs { 3, 3 };

    Matrix< Triple > out { 3, 3 };

    lhs [ 0 ] = std::vector< Double > { 1, 2, 3 };
    lhs [ 1 ] = std::vector< Double > { 4, 5, 6 };
    lhs [ 2 ] = std::vector< Double > { 7, 8, 9 };

    rhs [ 0 ] = std::vector< Triple > { 10, 11, 12 };
    rhs [ 1 ] = std::vector< Triple > { 13, 14, 15 };
    rhs [ 2 ] = std::vector< Triple > { 16, 17, 18 };

    out = lhs * rhs;

    Matrix< Triple > expect { 3, 3 };
    expect [ 0 ] = std::vector< Triple > { 1 * 10 + 2 * 13 + 3 * 16,
                                                1 * 11 + 2 * 14 + 3 * 17,
                                                1 * 12 + 2 * 15 + 3 * 18 };
    expect [ 1 ] = std::vector< Triple > { 4 * 10 + 5 * 13 + 6 * 16,
                                                4 * 11 + 5 * 14 + 6 * 17,
                                                4 * 12 + 5 * 15 + 6 * 18 };
    expect [ 2 ] = std::vector< Triple > { 7 * 10 + 8 * 13 + 9 * 16,
                                                7 * 11 + 8 * 14 + 9 * 17,
                                                7 * 12 + 8 * 15 + 9 * 18 };

    std::cout << "Expected: ";
    for ( std::size_t i = 0; i < 3; i++ )
    {
        std::cout << expect [ i ][ 0 ] << ", " << expect [ i ][ 1 ] << ", "
                  << expect [ i ][ 2 ] << "; ";
    }
    std::cout << "\n";
    std::cout << "Actual: ";
    for ( std::size_t i = 0; i < 3; i++ )
    {
        std::cout << out [ i ][ 0 ] << ", " << out [ i ][ 1 ] << ", "
                  << out [ i ][ 2 ] << "; ";
    }
    std::cout << "\n";
}

void testVectorMultiplication ( )
{
    using namespace ml;

    Matrix< Double > mat { 3, 3 };
    mat [ 0 ] = std::vector< Double > { 1, 2, 3 };
    mat [ 1 ] = std::vector< Double > { 4, 5, 6 };
    mat [ 2 ] = std::vector< Double > { 7, 8, 9 };

    std::vector< Double > input { 1, 1, 1 };

    std::vector< Double > expect = { 1 + 2 + 3, 4 + 5 + 6, 7 + 8 + 9 };

    std::vector< Double > result = mat * input;

    std::cout << "Expected: ";
    for ( auto &e : expect ) { std::cout << e << " "; }
    std::cout << "\nActual: ";
    for ( auto &a : result ) { std::cout << a << " "; }

    std::cout << "\n";
}