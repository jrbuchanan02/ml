/**
 * @file build.cc
 * @author Joshua Buchanan (joshuarobertbuchanan@gmail.com)
 * @brief Translates the functions present only in ml.hh from the functions
 * native to ml.
 * @version 1
 * @date 2022-04-15
 *
 * @copyright Copyright (C) 2022. Intellectual property of the author(s) listed
 * above.
 *
 */

#undef __IMPORT__
#include "code/math/matrix.hh"
#include "ml.hh"

#include <memory>

template class ml::Matrix< Single >;
template class ml::Matrix< Double >;
template class ml::Matrix< Triple >;

template < CONCEPT_NAMESPACE Floating V >
ml::Matrix< V > *asMatrix ( void *matrix )
{
    return ( ml::Matrix< V > * ) matrix;
}

template < CONCEPT_NAMESPACE Floating V >
void sizeofMatrixAlgorithm ( unsigned long long int *size )
{
    *size = sizeof ( ml::Matrix< V > );
}

template < CONCEPT_NAMESPACE Floating V >
void allocateMatrixAlgorithm ( void *pMatrix )
{
    new ( pMatrix ) ml::Matrix< V > ( );
}

template < CONCEPT_NAMESPACE Floating V >
void constructMatrixAlgorithm ( void                  *pMatrix,
                                unsigned long long int rows,
                                unsigned long long int cols )
{
    new ( pMatrix ) ml::Matrix< V > ( rows, cols );
}

template < CONCEPT_NAMESPACE Floating V >
void identityAlgorithm ( void *pMatrix, unsigned long long int size )
{
    allocateMatrixAlgorithm< V > ( pMatrix );
    *asMatrix< V > ( pMatrix ) = ml::Matrix< V >::identity ( size );
}

template < CONCEPT_NAMESPACE Floating V >
void deleteMatrixAlgorithm ( void *pMatrix )
{
    delete asMatrix< V > ( pMatrix );
}

template < CONCEPT_NAMESPACE Floating V >
void countRowsAlgorithm ( void *pMatrix, unsigned long long int *rows )
{
    *rows = asMatrix< V > ( pMatrix )->rowCount ( );
}

template < CONCEPT_NAMESPACE Floating V >
void countColsAlgorithm ( void *pMatrix, unsigned long long int *cols )
{
    *cols = asMatrix< V > ( pMatrix )->colCount ( );
}

template < CONCEPT_NAMESPACE Floating V >
int getIndexAlgorithm ( void                  *pMatrix,
                        unsigned long long int row,
                        unsigned long long int col,
                        V                     *x )
{
    try
    {
        *x = ( *asMatrix< V > ( pMatrix ) ) [ row ][ col ];
        return 0;
    } catch ( ... )
    {
        *x = 0.0;
        return -1;
    }
}

template < CONCEPT_NAMESPACE Floating V >
int setIndexAlgorithm ( void                  *pMatrix,
                        unsigned long long int row,
                        unsigned long long int col,
                        V                      x )
{
    try
    {
        ( *asMatrix< V > ( pMatrix ) ) [ row ][ col ] = x;
        return 0;
    } catch ( ... )
    {
        return -1;
    }
}

template < CONCEPT_NAMESPACE Floating V >
void copyMatrixAlgorithm ( void *lhs, void *rhs )
{
    *asMatrix< V > ( lhs ) = *asMatrix< V > ( rhs );
}

template < CONCEPT_NAMESPACE Floating V >
void moveMatrixAlgorithm ( void *lhs, void *rhs )
{
    *asMatrix< V > ( lhs ) = std::move ( *asMatrix< V > ( rhs ) );
}

template < CONCEPT_NAMESPACE Floating V, CONCEPT_NAMESPACE Floating W >
int addMatrixAndMatrixAlgorithm ( void *dst, void *lhs, void *rhs )
{
    ml::Matrix< V > *plhs = asMatrix< V > ( lhs );
    ml::Matrix< W > *prhs = asMatrix< W > ( rhs );
    if ( plhs->rowCount ( ) != prhs->rowCount ( )
         || plhs->colCount ( ) != prhs->colCount ( ) )
    {
        return -1;
    } else
    {
        constructMatrixAlgorithm< decltype ( V { 0 } + W { 0 } ) > (
                dst,
                plhs->rowCount ( ),
                prhs->rowCount ( ) );
        ml::Matrix< decltype ( V { 0 } + W { 0 } ) > *pdst =
                asMatrix< decltype ( V { 0 } + W { 0 } ) > ( dst );
        *pdst = *plhs + *prhs;
        return 0;
    }
}

template < CONCEPT_NAMESPACE Floating V, CONCEPT_NAMESPACE Floating W >
int subMatrixAndMatrixAlgorithm ( void *dst, void *lhs, void *rhs )
{
    ml::Matrix< V > *plhs = asMatrix< V > ( lhs );
    ml::Matrix< W > *prhs = asMatrix< W > ( rhs );
    if ( plhs->rowCount ( ) != prhs->rowCount ( )
         || plhs->colCount ( ) != prhs->colCount ( ) )
    {
        return -1;
    } else
    {
        constructMatrixAlgorithm< decltype ( V { 0 } + W { 0 } ) > (
                dst,
                plhs->rowCount ( ),
                prhs->rowCount ( ) );
        ml::Matrix< decltype ( V { 0 } + W { 0 } ) > *pdst =
                asMatrix< decltype ( V { 0 } + W { 0 } ) > ( dst );
        *pdst = *plhs - *prhs;
        return 0;
    }
}

template < CONCEPT_NAMESPACE Floating V, CONCEPT_NAMESPACE Floating W >
int mulMatrixAndMatrixAlgorithm ( void *dst, void *lhs, void *rhs )
{
    ml::Matrix< V > *plhs = asMatrix< V > ( lhs );
    ml::Matrix< W > *prhs = asMatrix< W > ( rhs );
    if ( plhs->rowCount ( ) != prhs->colCount ( )
         || plhs->colCount ( ) != prhs->rowCount ( ) )
    {
        return -1;
    } else
    {
        constructMatrixAlgorithm< decltype ( V { 0 } + W { 0 } ) > (
                dst,
                plhs->rowCount ( ),
                prhs->colCount ( ) );
        ml::Matrix< decltype ( V { 0 } + W { 0 } ) > *pdst =
                asMatrix< decltype ( V { 0 } + W { 0 } ) > ( dst );
        *pdst = *plhs * *prhs;
        return 0;
    }
}

template < CONCEPT_NAMESPACE Floating V, CONCEPT_NAMESPACE Floating W >
int evalMatrixAndVectorAlgorithm ( decltype ( V { 0 } + W { 0 } ) * dst,
                                   void                  *src,
                                   unsigned long long int len,
                                   W                     *vec )
{
    ml::Matrix< V > *psrc = asMatrix< V > ( src );
    if ( psrc->colCount ( ) != len )
    {
        return -1;
    } else
    {
        std::vector< W > values;
        for ( unsigned long long int i = 0; i < len; i++ )
        {
            values.push_back ( vec [ i ] );
        }

        auto temp = *psrc * values;
        for ( unsigned long long int i = 0; i < psrc->colCount ( ); i++ )
        {
            dst [ i ] = temp [ i ];
        }
        return 0;
    }
}

template < CONCEPT_NAMESPACE Floating V, CONCEPT_NAMESPACE Floating W >
void mulMatrixAndScalarAlgorithm ( void *dst, void *src, W scalar )
{
    ml::Matrix< V > *psrc = asMatrix< V > ( src );
    constructMatrixAlgorithm< decltype ( V { 0 } + W { 0 } ) > (
            dst,
            psrc->rowCount ( ),
            psrc->colCount ( ) );
    ml::Matrix< decltype ( V { 0 } + W { 0 } ) > *pdst =
            asMatrix< decltype ( V { 0 } + W { 0 } ) > ( dst );

    *pdst = *psrc * scalar;
}

template < CONCEPT_NAMESPACE Floating V, CONCEPT_NAMESPACE Floating W >
void divMatrixAndScalarAlgorithm ( void *dst, void *src, W scalar )
{
    ml::Matrix< V > *psrc = asMatrix< V > ( src );
    constructMatrixAlgorithm< decltype ( V { 0 } + W { 0 } ) > (
            dst,
            psrc->rowCount ( ),
            psrc->colCount ( ) );
    ml::Matrix< decltype ( V { 0 } + W { 0 } ) > *pdst =
            asMatrix< decltype ( V { 0 } + W { 0 } ) > ( dst );

    *pdst = *psrc / scalar;
}

template < CONCEPT_NAMESPACE Floating V, CONCEPT_NAMESPACE Floating W >
int augmentMatrixAndMatrixAlgorithm ( void *aug, void *lhs, void *rhs )
{
    ml::Matrix< V > *plhs = asMatrix< V > ( lhs );
    ml::Matrix< W > *prhs = asMatrix< W > ( rhs );
    if ( plhs->rowCount ( ) != prhs->rowCount ( ) )
    {
        return -1;
    } else
    {
        constructMatrixAlgorithm< decltype ( V { 0 } + W { 0 } ) > (
                aug,
                plhs->rowCount ( ),
                plhs->colCount ( ) + prhs->colCount ( ) );
        ml::Matrix< decltype ( V { 0 } + W { 0 } ) > *paug =
                asMatrix< decltype ( V { 0 } + W { 0 } ) > ( aug );
        *paug = plhs->augment ( *prhs );
        return 0;
    }
}

template < CONCEPT_NAMESPACE Floating V >
void echelonAlgorithm ( void *res, void *mat )
{
    ml::Matrix< V > *pmat = asMatrix< V > ( mat );
    constructMatrixAlgorithm< V > ( res,
                                    pmat->rowCount ( ),
                                    pmat->colCount ( ) );
    ml::Matrix< V > *pres = asMatrix< V > ( res );
    *pres                 = pmat->echelon ( );
}

template < CONCEPT_NAMESPACE Floating V >
int inverseAlgorithm ( void *res, void *mat )
{
    ml::Matrix< V > *pmat = asMatrix< V > ( mat );
    try
    {
        ml::Matrix< V > temp = pmat->inverse ( );
        constructMatrixAlgorithm< V > ( res,
                                        pmat->rowCount ( ),
                                        pmat->colCount ( ) );
        ml::Matrix< V > *pres = asMatrix< V > ( res );
        *pres                 = temp;
        return 0;
    } catch ( ... )
    {
        return -1;
    }
}

template < CONCEPT_NAMESPACE Floating V, CONCEPT_NAMESPACE Floating W >
int compareMatrixAndMatrixAlgorithm ( void *lhs, void *rhs )
{
    return *asMatrix< V > ( lhs ) == *asMatrix< W > ( rhs );
}

extern "C" {
#define EXPORT_FN_ONE_ARG( RET, NAME, ARG1, TYPE1 )                            \
    EXTERN RET NAME##OfSingles ( TYPE1 ARG1 )                                  \
    {                                                                          \
        return NAME##Algorithm< Single > ( ARG1 );                             \
    }                                                                          \
    EXTERN RET NAME##OfDoubles ( TYPE1 ARG1 )                                  \
    {                                                                          \
        return NAME##Algorithm< Double > ( ARG1 );                             \
    }                                                                          \
    EXTERN RET NAME##OfTriples ( TYPE1 ARG1 )                                  \
    {                                                                          \
        return NAME##Algorithm< Triple > ( ARG1 );                             \
    }

#define EXPORT_FN_TWO_ARG( RET, NAME, ARG1, TYPE1, ARG2, TYPE2 )               \
    EXTERN RET NAME##OfSingles ( TYPE1 ARG1, TYPE2 ARG2 )                      \
    {                                                                          \
        return NAME##Algorithm< Single > ( ARG1, ARG2 );                       \
    }                                                                          \
    EXTERN RET NAME##OfDoubles ( TYPE1 ARG1, TYPE2 ARG2 )                      \
    {                                                                          \
        return NAME##Algorithm< Double > ( ARG1, ARG2 );                       \
    }                                                                          \
    EXTERN RET NAME##OfTriples ( TYPE1 ARG1, TYPE2 ARG2 )                      \
    {                                                                          \
        return NAME##Algorithm< Triple > ( ARG1, ARG2 );                       \
    }

#define EXPORT_FN_3_ARGS( RET, NAME, ARG1, TYPE1, ARG2, TYPE2, ARG3, TYPE3 )   \
    EXTERN RET NAME##OfSingles ( TYPE1 ARG1, TYPE2 ARG2, TYPE3 ARG3 )          \
    {                                                                          \
        return NAME##Algorithm< Single > ( ARG1, ARG2, ARG3 );                 \
    }                                                                          \
    EXTERN RET NAME##OfDoubles ( TYPE1 ARG1, TYPE2 ARG2, TYPE3 ARG3 )          \
    {                                                                          \
        return NAME##Algorithm< Double > ( ARG1, ARG2, ARG3 );                 \
    }                                                                          \
    EXTERN RET NAME##OfTriples ( TYPE1 ARG1, TYPE2 ARG2, TYPE3 ARG3 )          \
    {                                                                          \
        return NAME##Algorithm< Triple > ( ARG1, ARG2, ARG3 );                 \
    }
#define EXPORT_FN_4_ARGS( RET,                                                 \
                          NAME,                                                \
                          ARG1,                                                \
                          TYPE1,                                               \
                          ARG2,                                                \
                          TYPE2,                                               \
                          ARG3,                                                \
                          TYPE3,                                               \
                          ARG4,                                                \
                          TYPE4 )                                              \
    EXTERN RET NAME##OfSingles ( TYPE1 ARG1,                                   \
                                 TYPE2 ARG2,                                   \
                                 TYPE3 ARG3,                                   \
                                 TYPE4 ARG4 )                                  \
    {                                                                          \
        return NAME##Algorithm< Single > ( ARG1, ARG2, ARG3, ARG4 );           \
    }                                                                          \
    EXTERN RET NAME##OfDoubles ( TYPE1 ARG1,                                   \
                                 TYPE2 ARG2,                                   \
                                 TYPE3 ARG3,                                   \
                                 TYPE4 ARG4 )                                  \
    {                                                                          \
        return NAME##Algorithm< Double > ( ARG1, ARG2, ARG3, ARG4 );           \
    }                                                                          \
    EXTERN RET NAME##OfTriples ( TYPE1 ARG1,                                   \
                                 TYPE2 ARG2,                                   \
                                 TYPE3 ARG3,                                   \
                                 TYPE4 ARG4 )                                  \
    {                                                                          \
        return NAME##Algorithm< Triple > ( ARG1, ARG2, ARG3, ARG4 );           \
    }
#define EXPORT_FN_4_ARGS_FINAL_IS_ELEM( RET,                                   \
                                        NAME,                                  \
                                        ARG1,                                  \
                                        TYPE1,                                 \
                                        ARG2,                                  \
                                        TYPE2,                                 \
                                        ARG3,                                  \
                                        TYPE3,                                 \
                                        ARG4 )                                 \
    EXTERN RET NAME##OfSingles ( TYPE1  ARG1,                                  \
                                 TYPE2  ARG2,                                  \
                                 TYPE3  ARG3,                                  \
                                 Single ARG4 )                                 \
    {                                                                          \
        return NAME##Algorithm< Single > ( ARG1, ARG2, ARG3, ARG4 );           \
    }                                                                          \
    EXTERN RET NAME##OfDoubles ( TYPE1  ARG1,                                  \
                                 TYPE2  ARG2,                                  \
                                 TYPE3  ARG3,                                  \
                                 Double ARG4 )                                 \
    {                                                                          \
        return NAME##Algorithm< Double > ( ARG1, ARG2, ARG3, ARG4 );           \
    }                                                                          \
    EXTERN RET NAME##OfTriples ( TYPE1  ARG1,                                  \
                                 TYPE2  ARG2,                                  \
                                 TYPE3  ARG3,                                  \
                                 Triple ARG4 )                                 \
    {                                                                          \
        return NAME##Algorithm< Triple > ( ARG1, ARG2, ARG3, ARG4 );           \
    }
#define EXPORT_FN_4_ARGS_FINAL_IS_ELEM_PTR( RET,                               \
                                            NAME,                              \
                                            ARG1,                              \
                                            TYPE1,                             \
                                            ARG2,                              \
                                            TYPE2,                             \
                                            ARG3,                              \
                                            TYPE3,                             \
                                            ARG4 )                             \
    EXTERN RET NAME##OfSingles ( TYPE1   ARG1,                                 \
                                 TYPE2   ARG2,                                 \
                                 TYPE3   ARG3,                                 \
                                 Single *ARG4 )                                \
    {                                                                          \
        return NAME##Algorithm< Single > ( ARG1, ARG2, ARG3, ARG4 );           \
    }                                                                          \
    EXTERN RET NAME##OfDoubles ( TYPE1   ARG1,                                 \
                                 TYPE2   ARG2,                                 \
                                 TYPE3   ARG3,                                 \
                                 Double *ARG4 )                                \
    {                                                                          \
        return NAME##Algorithm< Double > ( ARG1, ARG2, ARG3, ARG4 );           \
    }                                                                          \
    EXTERN RET NAME##OfTriples ( TYPE1   ARG1,                                 \
                                 TYPE2   ARG2,                                 \
                                 TYPE3   ARG3,                                 \
                                 Triple *ARG4 )                                \
    {                                                                          \
        return NAME##Algorithm< Triple > ( ARG1, ARG2, ARG3, ARG4 );           \
    }
#define EXPORT_FN_MATRIX_MATRIX_BIN_OP( RET, NAME )                            \
    EXTERN RET NAME##SinglesAndSingles ( MatrixOfSingles dst,                  \
                                         MatrixOfSingles lhs,                  \
                                         MatrixOfSingles rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Single, Single > ( dst,         \
                                                                  lhs,         \
                                                                  rhs );       \
    }                                                                          \
    EXTERN RET NAME##SinglesAndDoubles ( MatrixOfDoubles dst,                  \
                                         MatrixOfSingles lhs,                  \
                                         MatrixOfDoubles rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Single, Double > ( dst,         \
                                                                  lhs,         \
                                                                  rhs );       \
    }                                                                          \
    EXTERN RET NAME##SinglesAndTriples ( MatrixOfTriples dst,                  \
                                         MatrixOfSingles lhs,                  \
                                         MatrixOfTriples rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Single, Triple > ( dst,         \
                                                                  lhs,         \
                                                                  rhs );       \
    }                                                                          \
    EXTERN RET NAME##DoublesAndSingles ( MatrixOfDoubles dst,                  \
                                         MatrixOfDoubles lhs,                  \
                                         MatrixOfSingles rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Double, Single > ( dst,         \
                                                                  lhs,         \
                                                                  rhs );       \
    }                                                                          \
    EXTERN RET NAME##DoublesAndDoubles ( MatrixOfDoubles dst,                  \
                                         MatrixOfDoubles lhs,                  \
                                         MatrixOfDoubles rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Double, Double > ( dst,         \
                                                                  lhs,         \
                                                                  rhs );       \
    }                                                                          \
    EXTERN RET NAME##DoublesAndTriples ( MatrixOfTriples dst,                  \
                                         MatrixOfDoubles lhs,                  \
                                         MatrixOfTriples rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Double, Triple > ( dst,         \
                                                                  lhs,         \
                                                                  rhs );       \
    }                                                                          \
    EXTERN RET NAME##TriplesAndSingles ( MatrixOfTriples dst,                  \
                                         MatrixOfTriples lhs,                  \
                                         MatrixOfSingles rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Triple, Single > ( dst,         \
                                                                  lhs,         \
                                                                  rhs );       \
    }                                                                          \
    EXTERN RET NAME##TriplesAndDoubles ( MatrixOfTriples dst,                  \
                                         MatrixOfTriples lhs,                  \
                                         MatrixOfDoubles rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Triple, Double > ( dst,         \
                                                                  lhs,         \
                                                                  rhs );       \
    }                                                                          \
    EXTERN RET NAME##TriplesAndTriples ( MatrixOfTriples dst,                  \
                                         MatrixOfTriples lhs,                  \
                                         MatrixOfTriples rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Triple, Triple > ( dst,         \
                                                                  lhs,         \
                                                                  rhs );       \
    }
#define EXPORT_FN_MATRIX_VECTOR_BIN_OP( RET, NAME )                            \
    EXTERN RET NAME##SinglesWithSingle ( Single         *res,                  \
                                         MatrixOfSingles src,                  \
                                         size_y          len,                  \
                                         Single         *vec )                 \
    {                                                                          \
        return NAME##MatrixAndVectorAlgorithm< Single, Single > ( res,         \
                                                                  src,         \
                                                                  len,         \
                                                                  vec );       \
    }                                                                          \
    EXTERN RET NAME##SinglesWithDouble ( Double         *res,                  \
                                         MatrixOfSingles src,                  \
                                         size_y          len,                  \
                                         Double         *vec )                 \
    {                                                                          \
        return NAME##MatrixAndVectorAlgorithm< Single, Double > ( res,         \
                                                                  src,         \
                                                                  len,         \
                                                                  vec );       \
    }                                                                          \
    EXTERN RET NAME##SinglesWithTriple ( Triple         *res,                  \
                                         MatrixOfSingles src,                  \
                                         size_y          len,                  \
                                         Triple         *vec )                 \
    {                                                                          \
        return NAME##MatrixAndVectorAlgorithm< Single, Triple > ( res,         \
                                                                  src,         \
                                                                  len,         \
                                                                  vec );       \
    }                                                                          \
    EXTERN RET NAME##DoublesWithSingle ( Double         *res,                  \
                                         MatrixOfDoubles src,                  \
                                         size_y          len,                  \
                                         Single         *vec )                 \
    {                                                                          \
        return NAME##MatrixAndVectorAlgorithm< Double, Single > ( res,         \
                                                                  src,         \
                                                                  len,         \
                                                                  vec );       \
    }                                                                          \
    EXTERN RET NAME##DoublesWithDouble ( Double         *res,                  \
                                         MatrixOfDoubles src,                  \
                                         size_y          len,                  \
                                         Double         *vec )                 \
    {                                                                          \
        return NAME##MatrixAndVectorAlgorithm< Double, Double > ( res,         \
                                                                  src,         \
                                                                  len,         \
                                                                  vec );       \
    }                                                                          \
    EXTERN RET NAME##DoublesWithTriple ( Triple         *res,                  \
                                         MatrixOfDoubles src,                  \
                                         size_y          len,                  \
                                         Triple         *vec )                 \
    {                                                                          \
        return NAME##MatrixAndVectorAlgorithm< Double, Triple > ( res,         \
                                                                  src,         \
                                                                  len,         \
                                                                  vec );       \
    }                                                                          \
    EXTERN RET NAME##TriplesWithSingle ( Triple         *res,                  \
                                         MatrixOfTriples src,                  \
                                         size_y          len,                  \
                                         Single         *vec )                 \
    {                                                                          \
        return NAME##MatrixAndVectorAlgorithm< Triple, Single > ( res,         \
                                                                  src,         \
                                                                  len,         \
                                                                  vec );       \
    }                                                                          \
    EXTERN RET NAME##TriplesWithDouble ( Triple         *res,                  \
                                         MatrixOfTriples src,                  \
                                         size_y          len,                  \
                                         Double         *vec )                 \
    {                                                                          \
        return NAME##MatrixAndVectorAlgorithm< Triple, Double > ( res,         \
                                                                  src,         \
                                                                  len,         \
                                                                  vec );       \
    }                                                                          \
    EXTERN RET NAME##TriplesWithTriple ( Triple         *res,                  \
                                         MatrixOfTriples src,                  \
                                         size_y          len,                  \
                                         Triple         *vec )                 \
    {                                                                          \
        return NAME##MatrixAndVectorAlgorithm< Triple, Triple > ( res,         \
                                                                  src,         \
                                                                  len,         \
                                                                  vec );       \
    }
#define EXPORT_FN_MATRIX_SCALAR_BIN_OP( RET, NAME )                            \
    EXTERN RET NAME##SinglesAndSingle ( MatrixOfSingles dst,                   \
                                        MatrixOfSingles src,                   \
                                        Single          x )                    \
    {                                                                          \
        return NAME##MatrixAndScalarAlgorithm< Single, Single > ( dst,         \
                                                                  src,         \
                                                                  x );         \
    }                                                                          \
    EXTERN RET NAME##SinglesAndDouble ( MatrixOfDoubles dst,                   \
                                        MatrixOfSingles src,                   \
                                        Double          x )                    \
    {                                                                          \
        return NAME##MatrixAndScalarAlgorithm< Single, Double > ( dst,         \
                                                                  src,         \
                                                                  x );         \
    }                                                                          \
    EXTERN RET NAME##SinglesAndTriple ( MatrixOfTriples dst,                   \
                                        MatrixOfSingles src,                   \
                                        Triple          x )                    \
    {                                                                          \
        return NAME##MatrixAndScalarAlgorithm< Single, Triple > ( dst,         \
                                                                  src,         \
                                                                  x );         \
    }                                                                          \
    EXTERN RET NAME##DoublesAndSingle ( MatrixOfDoubles dst,                   \
                                        MatrixOfDoubles src,                   \
                                        Single          x )                    \
    {                                                                          \
        return NAME##MatrixAndScalarAlgorithm< Double, Single > ( dst,         \
                                                                  src,         \
                                                                  x );         \
    }                                                                          \
    EXTERN RET NAME##DoublesAndDouble ( MatrixOfDoubles dst,                   \
                                        MatrixOfDoubles src,                   \
                                        Double          x )                    \
    {                                                                          \
        return NAME##MatrixAndScalarAlgorithm< Double, Double > ( dst,         \
                                                                  src,         \
                                                                  x );         \
    }                                                                          \
    EXTERN RET NAME##DoublesAndTriple ( MatrixOfTriples dst,                   \
                                        MatrixOfDoubles src,                   \
                                        Triple          x )                    \
    {                                                                          \
        return NAME##MatrixAndScalarAlgorithm< Double, Triple > ( dst,         \
                                                                  src,         \
                                                                  x );         \
    }                                                                          \
    EXTERN RET NAME##TriplesAndSingle ( MatrixOfTriples dst,                   \
                                        MatrixOfTriples src,                   \
                                        Single          x )                    \
    {                                                                          \
        return NAME##MatrixAndScalarAlgorithm< Triple, Single > ( dst,         \
                                                                  src,         \
                                                                  x );         \
    }                                                                          \
    EXTERN RET NAME##TriplesAndDouble ( MatrixOfTriples dst,                   \
                                        MatrixOfTriples src,                   \
                                        Double          x )                    \
    {                                                                          \
        return NAME##MatrixAndScalarAlgorithm< Triple, Double > ( dst,         \
                                                                  src,         \
                                                                  x );         \
    }                                                                          \
    EXTERN RET NAME##TriplesAndTriple ( MatrixOfTriples dst,                   \
                                        MatrixOfTriples src,                   \
                                        Triple          x )                    \
    {                                                                          \
        return NAME##MatrixAndScalarAlgorithm< Triple, Triple > ( dst,         \
                                                                  src,         \
                                                                  x );         \
    }

#define EXPORT_FN_MATRIX_COMPARE( RET, NAME )                                  \
    EXTERN RET NAME##SinglesAndSingles ( MatrixOfSingles lhs,                  \
                                         MatrixOfSingles rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Single, Single > ( lhs, rhs );  \
    }                                                                          \
    EXTERN RET NAME##SinglesAndDoubles ( MatrixOfSingles lhs,                  \
                                         MatrixOfDoubles rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Single, Double > ( lhs, rhs );  \
    }                                                                          \
    EXTERN RET NAME##SinglesAndTriples ( MatrixOfSingles lhs,                  \
                                         MatrixOfTriples rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Single, Triple > ( lhs, rhs );  \
    }                                                                          \
    EXTERN RET NAME##DoublesAndSingles ( MatrixOfDoubles lhs,                  \
                                         MatrixOfSingles rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Double, Single > ( lhs, rhs );  \
    }                                                                          \
    EXTERN RET NAME##DoublesAndDoubles ( MatrixOfDoubles lhs,                  \
                                         MatrixOfDoubles rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Double, Double > ( lhs, rhs );  \
    }                                                                          \
    EXTERN RET NAME##DoublesAndTriples ( MatrixOfTriples lhs,                  \
                                         MatrixOfTriples rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Double, Triple > ( lhs, rhs );  \
    }                                                                          \
    EXTERN RET NAME##TriplesAndSingles ( MatrixOfTriples lhs,                  \
                                         MatrixOfSingles rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Triple, Single > ( lhs, rhs );  \
    }                                                                          \
    EXTERN RET NAME##TriplesAndDoubles ( MatrixOfTriples lhs,                  \
                                         MatrixOfDoubles rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Triple, Double > ( lhs, rhs );  \
    }                                                                          \
    EXTERN RET NAME##TriplesAndTriples ( MatrixOfTriples lhs,                  \
                                         MatrixOfTriples rhs )                 \
    {                                                                          \
        return NAME##MatrixAndMatrixAlgorithm< Triple, Triple > ( lhs, rhs );  \
    }

    EXPORT_FN_ONE_ARG ( void, sizeofMatrix, size, size_y * )

    EXPORT_FN_ONE_ARG ( void, allocateMatrix, matrix, void * )

    EXPORT_FN_3_ARGS ( void,
                       constructMatrix,
                       matrix,
                       void *,
                       rows,
                       size_y,
                       cols,
                       size_y )

    EXPORT_FN_TWO_ARG ( void, identity, matrix, void *, size, size_y )

    EXPORT_FN_ONE_ARG ( void, deleteMatrix, matrix, void * )

    EXPORT_FN_4_ARGS_FINAL_IS_ELEM_PTR ( int,
                                         getIndex,
                                         matrix,
                                         void *,
                                         row,
                                         size_y,
                                         col,
                                         size_y,
                                         result )
    EXPORT_FN_4_ARGS_FINAL_IS_ELEM ( int,
                                     setIndex,
                                     matrix,
                                     void *,
                                     row,
                                     size_y,
                                     col,
                                     size_y,
                                     result )

    EXPORT_FN_TWO_ARG ( void, copyMatrix, lhs, void *, rhs, void * )
    EXPORT_FN_TWO_ARG ( void, moveMatrix, lhs, void *, rhs, void * )

    EXPORT_FN_MATRIX_MATRIX_BIN_OP ( int, add )
    EXPORT_FN_MATRIX_MATRIX_BIN_OP ( int, sub )
    EXPORT_FN_MATRIX_MATRIX_BIN_OP ( int, mul )

    EXPORT_FN_MATRIX_VECTOR_BIN_OP ( int, eval )

    EXPORT_FN_MATRIX_SCALAR_BIN_OP ( void, mul )
    EXPORT_FN_MATRIX_SCALAR_BIN_OP ( void, div )

    EXPORT_FN_TWO_ARG ( void, countRows, matrix, void *, out, size_y * )
    EXPORT_FN_TWO_ARG ( void, countCols, matrix, void *, out, size_y * )

    EXPORT_FN_MATRIX_MATRIX_BIN_OP ( int, augment )

    EXPORT_FN_TWO_ARG ( void, echelon, res, void *, mat, void * )
    EXPORT_FN_TWO_ARG ( int, inverse, res, void *, mat, void * )

    EXPORT_FN_MATRIX_COMPARE ( int, compare )
}