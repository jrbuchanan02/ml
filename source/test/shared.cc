/**
 * @file shared.cc
 * @author Joshua Buchanan (joshuarobertbuchanan@gmail.com)
 * @brief Shared library test
 * @version 1
 * @date 2022-04-15
 *
 * @copyright Copyright (C) 2022. Intellectual property of the author(s) listed
 * above.
 *
 */
#define __IMPORT__

#include "intf/ml.hh"

#include <iostream>

void testMatrixAllocateAndFill ( );
void testMatrixVectorMultiplication ( );
void testMatrixMatrixMultiplication ( );
void testEchelon ( );
void testInverse ( );

int main ( int const argc, char const *const *const argv )
{
    testMatrixAllocateAndFill ( );
    testMatrixVectorMultiplication ( );
}

void setIndex ( MatrixOfDoubles matrix, size_y r, size_y c, double val )
{
    if ( setIndexOfDoubles ( matrix, r, c, val ) )
    {
        std::cout << "Failed to set index " << r << ", " << c << " to " << val
                  << "\n";
    } else
    {
        std::cout << "Successfully set index " << r << ", " << c << " to "
                  << val << "\n";
    }
}

void checkIndex ( MatrixOfDoubles matrix, size_y r, size_y c, double expect )
{
    double temp = 0.0;
    if ( getIndexOfDoubles ( matrix, r, c, &temp ) )
    {
        std::cout << "Failed to get item in index " << r << ", " << c << "!\n";
    } else if ( temp != expect )
    {
        std::cout << "Successfully got item in index " << r << ", " << c
                  << ", but it is ";
        std::cout << temp << " and not " << expect << "!\n";
    } else
    {
        std::cout << "Successfully got item in index " << r << ", c"
                  << " and its";
        std::cout << " value is " << temp << ", as expected.\n";
    }
}

void testMatrixAllocateAndFill ( )
{
    unsigned long long int size = 0;
    sizeofMatrixOfDoubles ( &size );
    std::cout << "Sizeof matrix of doubles: " << size << "\n";

    MatrixOfDoubles test = std::malloc ( size );

    allocateMatrixOfDoubles ( test );

    std::cout << "Allocated a matrix of doubles! \n";

    deleteMatrixOfDoubles ( test );

    std::cout << "Deallocated a matrix of doubles!\n";

    test = nullptr;

    std::cout << "Reallocating test...\n";
    test = std::malloc ( size );
    std::cout << "Constructing 3 x 3 matrix...\n";
    constructMatrixOfDoubles ( test, 3, 3 );
    std::cout << "Test is now a 3 x 3 matrix!\n";
    std::cout << "Filling test to match the invertable matrix "
                 "[1,2,3;4,5,6;7,8,8]...\n";
    setIndex ( test, 0, 0, 1 );
    setIndex ( test, 0, 1, 2 );
    setIndex ( test, 0, 2, 3 );
    setIndex ( test, 1, 0, 4 );
    setIndex ( test, 1, 1, 5 );
    setIndex ( test, 1, 2, 6 );
    setIndex ( test, 2, 0, 7 );
    setIndex ( test, 2, 1, 8 );
    setIndex ( test, 2, 2, 8 );
    std::cout << "Verifying results...\n";
    checkIndex ( test, 0, 0, 1 );
    checkIndex ( test, 0, 1, 2 );
    checkIndex ( test, 0, 2, 3 );
    checkIndex ( test, 1, 0, 4 );
    checkIndex ( test, 1, 1, 5 );
    checkIndex ( test, 1, 2, 6 );
    checkIndex ( test, 2, 0, 7 );
    checkIndex ( test, 2, 1, 8 );
    checkIndex ( test, 2, 2, 8 );
    std::cout << "Deallocating test for a second time...\n";
    deleteMatrixOfDoubles ( test );
    std::cout << "Deallocated test, cleaning up...\n";
    test = nullptr;
}

void testMatrixVectorMultiplication ( )
{
    MatrixOfDoubles        mat  = nullptr;
    unsigned long long int size = 0;
    sizeofMatrixOfDoubles ( &size );
    mat = std::malloc ( size );
    constructMatrixOfDoubles ( mat, 3, 3 );
    // fill.
    double matrix [] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    setIndexOfDoubles ( mat, 0, 0, matrix [ 0 ] );
    setIndexOfDoubles ( mat, 0, 1, matrix [ 1 ] );
    setIndexOfDoubles ( mat, 0, 2, matrix [ 2 ] );
    setIndexOfDoubles ( mat, 1, 0, matrix [ 3 ] );
    setIndexOfDoubles ( mat, 1, 1, matrix [ 4 ] );
    setIndexOfDoubles ( mat, 1, 2, matrix [ 5 ] );
    setIndexOfDoubles ( mat, 2, 0, matrix [ 6 ] );
    setIndexOfDoubles ( mat, 2, 1, matrix [ 7 ] );
    setIndexOfDoubles ( mat, 2, 2, matrix [ 8 ] );

    double  input [ 3 ]  = { 1, 1, 1 };
    double  expect [ 3 ] = { 1 + 2 + 3, 4 + 5 + 6, 7 + 8 + 9 };
    double *result       = new double [ 3 ];
    evalDoublesWithDouble ( result, mat, 3, input );

    std::cout << "Expected: ";
    for ( std::size_t i = 0; i < 3; i++ ) { std::cout << expect [ i ] << " "; }
    std::cout << "\n";
    std::cout << "Actual  : ";
    for ( std::size_t i = 0; i < 3; i++ ) { std::cout << result [ i ] << " "; }
    deleteMatrixOfDoubles ( mat );
    mat = nullptr;
    delete [] result;
    result = nullptr;
}