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
    testMatrixMatrixMultiplication ( );
    testEchelon ( );
    testInverse ( );
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
    std::cout << "\n";
    deleteMatrixOfDoubles ( mat );
    mat = nullptr;
    delete [] result;
    result = nullptr;
}

void testMatrixMatrixMultiplication ( )
{
    MatrixOfDoubles lhs;
    MatrixOfTriples rhs, out;

    unsigned long long int doubleSize = 0, tripleSize = 0;
    sizeofMatrixOfDoubles ( &doubleSize );
    sizeofMatrixOfTriples ( &tripleSize );

    lhs = std::malloc ( doubleSize );
    rhs = std::malloc ( tripleSize );
    out = std::malloc ( tripleSize );

    constructMatrixOfDoubles ( lhs, 3, 3 );
    constructMatrixOfTriples ( rhs, 3, 3 );

    double      lMatrix [] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    long double rMatrix [] = { 10, 11, 12, 13, 14, 15, 16, 17, 18 };

    setIndexOfDoubles ( lhs, 0, 0, lMatrix [ 0 ] );
    setIndexOfDoubles ( lhs, 0, 1, lMatrix [ 1 ] );
    setIndexOfDoubles ( lhs, 0, 2, lMatrix [ 2 ] );
    setIndexOfDoubles ( lhs, 1, 0, lMatrix [ 3 ] );
    setIndexOfDoubles ( lhs, 1, 1, lMatrix [ 4 ] );
    setIndexOfDoubles ( lhs, 1, 2, lMatrix [ 5 ] );
    setIndexOfDoubles ( lhs, 2, 0, lMatrix [ 6 ] );
    setIndexOfDoubles ( lhs, 2, 1, lMatrix [ 7 ] );
    setIndexOfDoubles ( lhs, 2, 2, lMatrix [ 8 ] );

    setIndexOfTriples ( rhs, 0, 0, rMatrix [ 0 ] );
    setIndexOfTriples ( rhs, 0, 1, rMatrix [ 1 ] );
    setIndexOfTriples ( rhs, 0, 2, rMatrix [ 2 ] );
    setIndexOfTriples ( rhs, 1, 0, rMatrix [ 3 ] );
    setIndexOfTriples ( rhs, 1, 1, rMatrix [ 4 ] );
    setIndexOfTriples ( rhs, 1, 2, rMatrix [ 5 ] );
    setIndexOfTriples ( rhs, 2, 0, rMatrix [ 6 ] );
    setIndexOfTriples ( rhs, 2, 1, rMatrix [ 7 ] );
    setIndexOfTriples ( rhs, 2, 2, rMatrix [ 8 ] );

    mulDoublesAndTriples ( out, lhs, rhs );

    long double expected [ 3 ][ 3 ] = {
            { 1 * 10 + 2 * 13 + 3 * 16,
              1 * 11 + 2 * 14 + 3 * 17,
              1 * 12 + 2 * 15 + 3 * 18 },
            { 4 * 10 + 5 * 13 + 6 * 16,
              4 * 11 + 5 * 14 + 6 * 17,
              4 * 12 + 5 * 15 + 6 * 18 },
            { 7 * 10 + 8 * 13 + 9 * 16,
              7 * 11 + 8 * 14 + 9 * 17,
              7 * 12 + 8 * 15 + 9 * 18 },
    };

    std::cout << "Expected: ";
    for ( std::size_t r = 0; r < 3; r++ )
    {
        // C++ arrays are column-major order, the opposite of ml Matrices.
        std::cout << expected [ r ][ 0 ] << ", " << expected [ r ][ 1 ] << ", "
                  << expected [ r ][ 2 ] << "; ";
    }

    std::cout << "\n";
    std::cout << "Actual  : ";
    for ( std::size_t r = 0; r < 3; r++ )
    {
        for ( std::size_t c = 0; c < 3; c++ )
        {
            long double temp = 0;
            getIndexOfTriples ( out, r, c, &temp );
            std::cout << temp;
            if ( c == 2 )
            {
                std::cout << "; ";
            } else
            {
                std::cout << ", ";
            }
        }
    }
    std::cout << "\n";
    deleteMatrixOfDoubles ( lhs );
    deleteMatrixOfTriples ( rhs );
    deleteMatrixOfTriples ( out );
    lhs = rhs = out = nullptr;
}

void testEchelon ( )
{
    MatrixOfDoubles        test = nullptr;
    unsigned long long int size = 0;
    sizeofMatrixOfDoubles ( &size );
    test = std::malloc ( size );
    constructMatrixOfDoubles ( test, 2, 2 );
    setIndexOfDoubles ( test, 0, 0, 1 );
    setIndexOfDoubles ( test, 0, 1, 2 );
    setIndexOfDoubles ( test, 1, 0, 3 );
    setIndexOfDoubles ( test, 1, 1, 4 );

    MatrixOfDoubles result = nullptr;
    result                 = std::malloc ( size );

    echelonOfDoubles ( result, test );

    std::cout << "Expected: [1, 0; 0, 1]\n";
    std::cout << "Actual  : [";
    double temp = 0;
    getIndexOfDoubles ( result, 0, 0, &temp );
    std::cout << temp;
    getIndexOfDoubles ( result, 0, 1, &temp );
    std::cout << ", " << temp << "; ";
    getIndexOfDoubles ( result, 1, 0, &temp );
    std::cout << temp;
    getIndexOfDoubles ( result, 1, 1, &temp );
    std::cout << ", " << temp << "]\n";

    deleteMatrixOfDoubles ( test );
    deleteMatrixOfDoubles ( result );

    test   = std::malloc ( size );
    result = std::malloc ( size );
    constructMatrixOfDoubles ( test, 3, 3 );

    double matrix3x3 [] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    for ( std::size_t r = 0; r < 3; r++ )
    {
        for ( std::size_t c = 0; c < 3; c++ )
        {
            setIndexOfDoubles ( test, r, c, matrix3x3 [ 3 * r + c ] );
        }
    }

    echelonOfDoubles ( result, test );

    std::cout << "Expected: [1, 0, -1, 0, 1, 2; 0, 0, 0]\n";
    std::cout << "Actual  : [";
    for ( std::size_t r = 0; r < 3; r++ )
    {
        for ( std::size_t c = 0; c < 3; c++ )
        {
            double temp = 0.0;
            getIndexOfDoubles ( result, r, c, &temp );
            std::cout << temp;
            if ( c == 2 )
            {
                if ( r == 2 )
                {
                    std::cout << "]\n";
                } else
                {
                    std::cout << "; ";
                }
            } else
            {
                std::cout << ", ";
            }
        }
    }

    deleteMatrixOfDoubles ( test );
    deleteMatrixOfDoubles ( result );

    test   = std::malloc ( size );
    result = std::malloc ( size );

    constructMatrixOfDoubles ( test, 3, 4 );
    double matrix3x4 [] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    for ( std::size_t r = 0; r < 3; r++ )
    {
        for ( std::size_t c = 0; c < 4; c++ )
        {
            setIndexOfDoubles ( test, r, c, matrix3x4 [ 4 * r + c ] );
        }
    }

    echelonOfDoubles ( result, test );

    std::cout << "Expected: [1, 0, -1, -2; 0, 1, 2, 3; 0, 0, 0, 0]\n";
    std::cout << "Actual  : [";
    for ( std::size_t r = 0; r < 3; r++ )
    {
        for ( std::size_t c = 0; c < 4; c++ )
        {
            double temp = 0;
            getIndexOfDoubles ( result, r, c, &temp );
            std::cout << temp;
            if ( c == 3 )
            {
                if ( r == 2 )
                {
                    std::cout << "]\n";
                } else
                {
                    std::cout << "; ";
                }
            } else
            {
                std::cout << ", ";
            }
        }
    }

    deleteMatrixOfDoubles ( test );
    deleteMatrixOfDoubles ( result );
    test   = nullptr;
    result = nullptr;
}

void testInverse ( )
{
    unsigned long long int size   = 0;
    MatrixOfDoubles        test   = nullptr;
    MatrixOfDoubles        result = nullptr;

    sizeofMatrixOfDoubles ( &size );

    test   = std::malloc ( size );
    result = std::malloc ( size );

    double matrix [] = { 1, 2, 3, 4, 5, 6, 7, 8, 8 };
    double invers [] =
            { -8.0 / 3, 8.0 / 3, -1.0, 10.0 / 3, -13.0 / 3, 2.0, -1, 2, -1 };

    constructMatrixOfDoubles ( test, 3, 3 );

    for ( std::size_t r = 0; r < 3; r++ )
    {
        for ( std::size_t c = 0; c < 3; c++ )
        {
            setIndexOfDoubles ( test, r, c, matrix [ 3 * r + c ] );
        }
    }

    inverseOfDoubles ( result, test );

    std::cout << "Expected: [";

    for ( std::size_t r = 0; r < 3; r++ )
    {
        for ( std::size_t c = 0; c < 3; c++ )
        {
            std::cout << invers [ 3 * r + c ];
            if ( c == 2 )
            {
                if ( r == 2 )
                {
                    std::cout << "]\n";
                } else
                {
                    std::cout << "; ";
                }
            } else
            {
                std::cout << ", ";
            }
        }
    }

    std::cout << "Actual  : [";

    for ( std::size_t r = 0; r < 3; r++ )
    {
        for ( std::size_t c = 0; c < 3; c++ )
        {
            double temp = 0;
            getIndexOfDoubles ( result, r, c, &temp );
            std::cout << temp;
            if ( c == 2 )
            {
                if ( r == 2 )
                {
                    std::cout << "]\n";
                } else
                {
                    std::cout << "; ";
                }
            } else
            {
                std::cout << ", ";
            }
        }
    }

    deleteMatrixOfDoubles ( test );
    deleteMatrixOfDoubles ( result );

    test   = nullptr;
    result = nullptr;
}