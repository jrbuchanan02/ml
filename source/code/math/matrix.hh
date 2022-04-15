/**
 * @file matrix.hh
 * @author Joshua Buchanan (joshuarobertbuchanan@gmail.com)
 * @brief A matrix with n rows and m columns
 * @version 1
 * @date 2022-04-13
 *
 * @copyright Copyright (C) 2022. Intellectual property of the author(s) listed
 * above.
 *
 */
#pragma once

#include "meta.hh"

#include <stdexcept>
#include <vector>

#include <iostream>

// if C++ 20, then use concepts to require floating point types.
// otherwise, just alias the term "Floating" to "class"
CONCEPT_NAMESPACE_BEGIN
#if HAS_CONCEPTS
template < class F >
concept Floating = std::floating_point< F >;
#else
#    define Floating class
#endif
CONCEPT_NAMESPACE_END

namespace ml
{

    template < CONCEPT_NAMESPACE Floating V > class Matrix
    {
        using Column = std::vector< V >;
        std::vector< Column > rows;
    public:
        Matrix ( ) = default;
        Matrix ( std::size_t const rows, std::size_t const cols );

        std::size_t rowCount ( ) const NOEXCEPT;
        std::size_t colCount ( ) const NOEXCEPT;

        std::vector< V >       &operator[] ( std::size_t );
        std::vector< V > const &operator[] ( std::size_t ) const;

        // the identity matrix.
        static inline Matrix< V > identity ( std::size_t i )
        {
            Matrix< V > output { i, i };
            for ( std::size_t x = 0; x < i; x++ )
            {
                output [ x ][ x ] = V { 1 };
            }
            return output;
        }

// allow multiple-argument indexing operators when they exist.
#if __cplusplus >= 202300
        V &operator[] ( std::size_t, std::size_t );

        V const &operator[] ( std::size_t row, std::size_t col ) const;
#endif // if __cplusplus >= 202300

        template < CONCEPT_NAMESPACE Floating W = V,
                   CONCEPT_NAMESPACE Floating X = decltype ( V { 0 }
                                                             + W { 0 } ) >
        Matrix< X > operator+ ( Matrix< W > const & );

        template < CONCEPT_NAMESPACE Floating W = V,
                   CONCEPT_NAMESPACE Floating X = decltype ( V { 0 }
                                                             + W { 0 } ) >
        Matrix< X > operator- ( Matrix< W > const & );

        template < CONCEPT_NAMESPACE Floating W = V,
                   CONCEPT_NAMESPACE Floating X = decltype ( V { 0 }
                                                             + W { 0 } ) >
        Matrix< X > operator* ( Matrix< W > const &that );

        template < CONCEPT_NAMESPACE Floating W = V,
                   CONCEPT_NAMESPACE Floating X = decltype ( V { 0 }
                                                             + W { 0 } ) >
        std::vector< X > operator* ( std::vector< W > const &input );

        template < CONCEPT_NAMESPACE Floating W = V,
                   CONCEPT_NAMESPACE Floating X = decltype ( V { 0 }
                                                             + W { 0 } ) >
        Matrix< X > operator* ( W const &scalar );

        template < CONCEPT_NAMESPACE Floating W = V,
                   CONCEPT_NAMESPACE Floating X = decltype ( V { 0 }
                                                             + W { 0 } ) >
        Matrix< X > operator/ ( W const &scalar );

        template < CONCEPT_NAMESPACE Floating W = V,
                   CONCEPT_NAMESPACE Floating X = decltype ( V { 0 }
                                                             + W { 0 } ) >
        Matrix< X > augment ( Matrix< W > const &rhs );

        /**
         * @brief Gets this in reduced row echelon form. I have not
         * mathematically proven that this algorithm is correct, but I have not
         * seen any indication that it performs anything dubious.
         * @note It solves it more like a human would tho, so there's perhaps
         * some optimizations possible.
         * @return Matrix<V> this in rref form.
         */
        Matrix< V > echelon ( ) const;

        /**
         * @brief Attempts to find the inverse of this matrix using the
         * superaugmented matrix technique (augmenting this with the appropriate
         * identity matrix and reducing to echelon form).
         * @note While this technique works, the only
         * time this function indicates that the inverse cannot be found is if
         * the matrix is not square and there are other conditions for no
         * inverse to exist.
         * @note Due to floating point precision issues, this function may not
         * return the exact inverse. This is because most numbers do not have
         * terminating decimals in binary floating point (as in, they have to
         * be linear combinations of powers of 2). The computer, as a result,
         * cannot differentiate say 0.1 and the nearest finite linear
         * combination of powers of 2. So, you may find that A * A.inverse() !=
         * identity(A.rowCount()); but the diference between A * A.inverse() and
         * identity(A.rowCount()) should be markedly small.
         * @internal This function should work in a constant context.
         * @return Matrix<V>
         */
        Matrix< V > inverse ( );

        template < CONCEPT_NAMESPACE Floating W = V >
        bool operator== ( Matrix< W > const &that ) const noexcept;
    };

} // namespace ml

#include "matrix.tcc"