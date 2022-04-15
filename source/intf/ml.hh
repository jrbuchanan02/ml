/**
 * @file ml.hh
 * @author Joshua Buchanan (joshuarobertbuchanan@gmail.com)
 * @brief This is the main include header for ML. This header supports building
 * as a source library (meaning that you can instantiate the templates yourself
 * and use all the code) or as a shared library (meaning that the code is
 * precompiled for you). As a source library, ML must be compiled with C++.
 * @note All results assume a properly sized buffer but no matrix at the
 * destination pointer.
 * @note The source matrix after a move operation should be considered
 * undefined.
 * @note Always pair getting the destination of a matrix or constructing a
 * matrix with deleting the matrix.
 * @note I decided not to alias types in this file other than the aliases 
 * present in this file because I don't want to make every dependent of ML 
 * include the meta.hh file since that source may define its own aliases.
 * @version 1
 * @date 2022-04-15
 *
 * @copyright Copyright (C) 2022. Intellectual property of the author(s) listed
 * above.
 *
 */
#pragma once

#ifdef __SOURCE_LIBRARY_ML__
#    ifndef __cplusplus
#        error "ML is written in C++ and will not function as a source library in any other language"
#    endif // ifndef __cplusplus

#    include "meta.hh"

#    include "code/math/matrix.hh"

#endif // ifdef __SOURCE_LIBRARY_ML__

// shared library shenanegans
#ifdef __IMPORT__
#    define EXTERN extern
#else
#    define EXTERN
#endif

#ifdef __cplusplus
extern "C" {
#endif

    typedef void                  *MatrixOfSingles; // Matrix<float>
    typedef void                  *MatrixOfDoubles; // Matrix<double>
    typedef void                  *MatrixOfTriples; // Matrix<long double>
    typedef unsigned long long int size_y;

    // functions to get the size of the matrix type.
    EXTERN void sizeofMatrixOfSingles ( size_y * );
    EXTERN void sizeofMatrixOfDoubles ( size_y * );
    EXTERN void sizeofMatrixOfTriples ( size_y * );

    // functions within the matrix type.
    // allocators i.e., default constructors.
    EXTERN void allocateMatrixOfSingles ( MatrixOfSingles );
    EXTERN void allocateMatrixOfDoubles ( MatrixOfDoubles );
    EXTERN void allocateMatrixOfTriples ( MatrixOfTriples );

    // constructors, i.e., the explicit {rows, cols} constructors.
    EXTERN void constructMatrixOfSingles ( MatrixOfSingles, size_y, size_y );
    EXTERN void constructMatrixOfDoubles ( MatrixOfDoubles, size_y, size_y );
    EXTERN void constructMatrixOfTriples ( MatrixOfTriples, size_y, size_y );

    // construct the identity matrix
    EXTERN void identityOfSingles ( MatrixOfSingles, size_y );
    EXTERN void identityOfDoubles ( MatrixOfDoubles, size_y );
    EXTERN void identityOfTriples ( MatrixOfTriples, size_y );

    // destructors, i.e., calls delete on the allocation (after cast to
    // appropriate type)
    EXTERN void deleteMatrixOfSingles ( MatrixOfSingles );
    EXTERN void deleteMatrixOfDoubles ( MatrixOfDoubles );
    EXTERN void deleteMatrixOfTriples ( MatrixOfTriples );

    EXTERN void countRowsOfSingles ( MatrixOfSingles, size_y * );
    EXTERN void countRowsOfDoubles ( MatrixOfDoubles, size_y * );
    EXTERN void countRowsOfTriples ( MatrixOfTriples, size_y * );
    EXTERN void countColsOfSingles ( MatrixOfSingles, size_y * );
    EXTERN void countColsOfDoubles ( MatrixOfDoubles, size_y * );
    EXTERN void countColsOfTriples ( MatrixOfTriples, size_y * );

    // indexers. Return nonzero if out of bounds since throwing exceptions don't
    // apply in C.
    EXTERN int getIndexOfSingles ( MatrixOfSingles, size_y, size_y, float * );
    EXTERN int getIndexOfDoubles ( MatrixOfDoubles, size_y, size_y, double * );
    EXTERN int getIndexOfTriples ( MatrixOfTriples,
                                   size_y,
                                   size_y,
                                   long double * );

    EXTERN int setIndexOfSingles ( MatrixOfSingles, size_y, size_y, float );
    EXTERN int setIndexOfDoubles ( MatrixOfDoubles, size_y, size_y, double );
    EXTERN int
            setIndexOfTriples ( MatrixOfTriples, size_y, size_y, long double );

    // lhs <- rhs
    EXTERN void copyMatrixOfSingles ( MatrixOfSingles, MatrixOfSingles );
    EXTERN void copyMatrixOfDoubles ( MatrixOfDoubles, MatrixOfDoubles );
    EXTERN void copyMatrixOfTriples ( MatrixOfTriples, MatrixOfTriples );
    EXTERN void moveMatrixOfSingles ( MatrixOfSingles, MatrixOfSingles );
    EXTERN void moveMatrixOfDoubles ( MatrixOfDoubles, MatrixOfDoubles );
    EXTERN void moveMatrixOfTriples ( MatrixOfTriples, MatrixOfTriples );

    // operators.

    // dst <- lhs op rhs. Does nothing if dimension mismatch (only reason for an
    // exception to throw)
    EXTERN int addSinglesAndSingles ( MatrixOfSingles,
                                      MatrixOfSingles,
                                      MatrixOfSingles );
    EXTERN int addSinglesAndDoubles ( MatrixOfDoubles,
                                      MatrixOfSingles,
                                      MatrixOfDoubles );
    EXTERN int addSinglesAndTriples ( MatrixOfTriples,
                                      MatrixOfSingles,
                                      MatrixOfTriples );
    EXTERN int addDoublesAndSingles ( MatrixOfDoubles,
                                      MatrixOfDoubles,
                                      MatrixOfSingles );
    EXTERN int addDoublesAndDoubles ( MatrixOfDoubles,
                                      MatrixOfDoubles,
                                      MatrixOfDoubles );
    EXTERN int addDoublesAndTriples ( MatrixOfTriples,
                                      MatrixOfDoubles,
                                      MatrixOfTriples );
    EXTERN int addTriplesAndSingles ( MatrixOfTriples,
                                      MatrixOfTriples,
                                      MatrixOfSingles );
    EXTERN int addTriplesAndDoubles ( MatrixOfTriples,
                                      MatrixOfTriples,
                                      MatrixOfDoubles );
    EXTERN int addTriplesAndTriples ( MatrixOfTriples,
                                      MatrixOfTriples,
                                      MatrixOfTriples );
    EXTERN int subSinglesAndSingles ( MatrixOfSingles,
                                      MatrixOfSingles,
                                      MatrixOfSingles );
    EXTERN int subSinglesAndDoubles ( MatrixOfDoubles,
                                      MatrixOfSingles,
                                      MatrixOfDoubles );
    EXTERN int subSinglesAndTriples ( MatrixOfTriples,
                                      MatrixOfSingles,
                                      MatrixOfTriples );
    EXTERN int subDoublesAndSingles ( MatrixOfDoubles,
                                      MatrixOfDoubles,
                                      MatrixOfSingles );
    EXTERN int subDoublesAndDoubles ( MatrixOfDoubles,
                                      MatrixOfDoubles,
                                      MatrixOfDoubles );
    EXTERN int subDoublesAndTriples ( MatrixOfTriples,
                                      MatrixOfDoubles,
                                      MatrixOfTriples );
    EXTERN int subTriplesAndSingles ( MatrixOfTriples,
                                      MatrixOfTriples,
                                      MatrixOfSingles );
    EXTERN int subTriplesAndDoubles ( MatrixOfTriples,
                                      MatrixOfTriples,
                                      MatrixOfDoubles );
    EXTERN int subTriplesAndTriples ( MatrixOfTriples,
                                      MatrixOfTriples,
                                      MatrixOfTriples );
    EXTERN int mulSinglesAndSingles ( MatrixOfSingles,
                                      MatrixOfSingles,
                                      MatrixOfSingles );
    EXTERN int mulSinglesAndDoubles ( MatrixOfDoubles,
                                      MatrixOfSingles,
                                      MatrixOfDoubles );
    EXTERN int mulSinglesAndTriples ( MatrixOfTriples,
                                      MatrixOfSingles,
                                      MatrixOfTriples );
    EXTERN int mulDoublesAndSingles ( MatrixOfDoubles,
                                      MatrixOfDoubles,
                                      MatrixOfSingles );
    EXTERN int mulDoublesAndDoubles ( MatrixOfDoubles,
                                      MatrixOfDoubles,
                                      MatrixOfDoubles );
    EXTERN int mulDoublesAndTriples ( MatrixOfTriples,
                                      MatrixOfDoubles,
                                      MatrixOfTriples );
    EXTERN int mulTriplesAndSingles ( MatrixOfTriples,
                                      MatrixOfTriples,
                                      MatrixOfSingles );
    EXTERN int mulTriplesAndDoubles ( MatrixOfTriples,
                                      MatrixOfTriples,
                                      MatrixOfDoubles );
    EXTERN int mulTriplesAndTriples ( MatrixOfTriples,
                                      MatrixOfTriples,
                                      MatrixOfTriples );

    // B <- A * x
    // where B is first arg, A is second arg, third arg is length of x, fourth
    // arg is x. Note: all of these temporarily construct an instance of
    // std::vector and will probably segfault if given the wrong size. Note:
    // assumes that the buffer is the correct length because this program
    // assumes you know how to use matrices.
    EXTERN int
            evalSinglesWithSingle ( float *, MatrixOfSingles, size_y, float * );
    EXTERN int evalSinglesWithDouble ( double *,
                                       MatrixOfSingles,
                                       size_y,
                                       double * );
    EXTERN int evalSinglesWithTriple ( long double *,
                                       MatrixOfSingles,
                                       size_y,
                                       long double * );

    EXTERN int evalDoublesWithSingle ( double *,
                                       MatrixOfDoubles,
                                       size_y,
                                       float * );
    EXTERN int evalDoublesWithDouble ( double *,
                                       MatrixOfDoubles,
                                       size_y,
                                       double * );
    EXTERN int evalDoublesWithTriple ( long double *,
                                       MatrixOfDoubles,
                                       size_y,
                                       long double * );

    EXTERN int evalTriplesWithSingle ( long double *,
                                       MatrixOfTriples,
                                       size_y,
                                       float * );
    EXTERN int evalTriplesWithDouble ( long double *,
                                       MatrixOfTriples,
                                       size_y,
                                       double * );
    EXTERN int evalTriplesWithTriple ( long double *,
                                       MatrixOfTriples,
                                       size_y,
                                       long double * );

    // dst <- lhs * rhs
    // it's scalar multiplication on matrices, what more is there to say?
    EXTERN void mulSinglesAndSingle ( MatrixOfSingles, MatrixOfSingles, float );
    EXTERN void
            mulSinglesAndDouble ( MatrixOfDoubles, MatrixOfSingles, double );
    EXTERN void mulSinglesAndTriple ( MatrixOfTriples,
                                      MatrixOfSingles,
                                      long double );

    EXTERN void mulDoublesAndSingle ( MatrixOfDoubles, MatrixOfDoubles, float );
    EXTERN void
            mulDoublesAndDouble ( MatrixOfDoubles, MatrixOfDoubles, double );
    EXTERN void mulDoublesAndTriple ( MatrixOfTriples,
                                      MatrixOfDoubles,
                                      long double );

    EXTERN void mulTriplesAndSingle ( MatrixOfTriples, MatrixOfTriples, float );
    EXTERN void
            mulTriplesAndDouble ( MatrixOfTriples, MatrixOfTriples, double );
    EXTERN void mulTriplesAndTriple ( MatrixOfTriples,
                                      MatrixOfTriples,
                                      long double );

    // all of these are shorthand for B <= A * (1 / x). Strictly speaking,
    // matrix division doesn't really exist.
    EXTERN void divSinglesAndSingle ( MatrixOfSingles, MatrixOfSingles, float );
    EXTERN void
            divSinglesAndDouble ( MatrixOfDoubles, MatrixOfSingles, double );
    EXTERN void divSinglesAndTriple ( MatrixOfTriples,
                                      MatrixOfSingles,
                                      long double );

    EXTERN void divDoublesAndSingle ( MatrixOfDoubles, MatrixOfDoubles, float );
    EXTERN void
            divDoublesAndDouble ( MatrixOfDoubles, MatrixOfDoubles, double );
    EXTERN void divDoublesAndTriple ( MatrixOfTriples,
                                      MatrixOfDoubles,
                                      long double );

    EXTERN void divTriplesAndSingle ( MatrixOfTriples, MatrixOfTriples, float );
    EXTERN void
            divTriplesAndDouble ( MatrixOfTriples, MatrixOfTriples, double );
    EXTERN void divTriplesAndTriple ( MatrixOfTriples,
                                      MatrixOfTriples,
                                      long double );

    // augment matrix a with matrix b to get matrix c.
    // only fails when a and b have different numbers of rows.
    EXTERN int augmentSinglesAndSingles ( MatrixOfSingles,
                                          MatrixOfSingles,
                                          MatrixOfSingles );
    EXTERN int augmentSinglesAndDoubles ( MatrixOfDoubles,
                                          MatrixOfSingles,
                                          MatrixOfDoubles );
    EXTERN int augmentSinglesAndTriples ( MatrixOfTriples,
                                          MatrixOfSingles,
                                          MatrixOfTriples );

    EXTERN int augmentDoublesAndSingles ( MatrixOfDoubles,
                                          MatrixOfDoubles,
                                          MatrixOfSingles );
    EXTERN int augmentDoublesAndDoubles ( MatrixOfDoubles,
                                          MatrixOfDoubles,
                                          MatrixOfDoubles );
    EXTERN int augmentDoublesAndTriples ( MatrixOfTriples,
                                          MatrixOfDoubles,
                                          MatrixOfTriples );

    EXTERN int augmentTriplesAndSingles ( MatrixOfTriples,
                                          MatrixOfTriples,
                                          MatrixOfSingles );
    EXTERN int augmentTriplesAndDoubles ( MatrixOfTriples,
                                          MatrixOfTriples,
                                          MatrixOfDoubles );
    EXTERN int augmentTriplesAndTriples ( MatrixOfTriples,
                                          MatrixOfTriples,
                                          MatrixOfTriples );

    EXTERN void echelonOfSingles ( MatrixOfSingles, MatrixOfSingles );
    EXTERN void echelonOfDoubles ( MatrixOfDoubles, MatrixOfDoubles );
    EXTERN void echelonOfTriples ( MatrixOfTriples, MatrixOfTriples );

    // not all matrices have inverses, it is an error, for example, if
    // the matrix is not square.
    EXTERN int inverseOfSingles ( MatrixOfSingles, MatrixOfSingles );
    EXTERN int inverseOfDoubles ( MatrixOfDoubles, MatrixOfDoubles );
    EXTERN int inverseOfTriples ( MatrixOfTriples, MatrixOfTriples );

    // returns nonzero if equal
    EXTERN int compareSinglesAndSingles ( MatrixOfSingles, MatrixOfSingles );
    EXTERN int compareSinglesAndDoubles ( MatrixOfSingles, MatrixOfDoubles );
    EXTERN int compareSinglesAndTriples ( MatrixOfSingles, MatrixOfTriples );
    EXTERN int compareDoublesAndSingles ( MatrixOfDoubles, MatrixOfSingles );
    EXTERN int compareDoublesAndDoubles ( MatrixOfDoubles, MatrixOfDoubles );
    EXTERN int compareDoublesAndTriples ( MatrixOfDoubles, MatrixOfTriples );
    EXTERN int compareTriplesAndSingles ( MatrixOfTriples, MatrixOfSingles );
    EXTERN int compareTriplesAndDoubles ( MatrixOfTriples, MatrixOfDoubles );
    EXTERN int compareTriplesAndTriples ( MatrixOfTriples, MatrixOfTriples );

#ifdef __cplusplus
}
#endif