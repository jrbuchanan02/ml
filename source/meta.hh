/**
 * @file meta.hh
 * @author Joshua Buchanan (joshuarobertbuchanan@gmail.com)
 * @brief Metaprogramming thingies
 * @version 1
 * @date 2022-04-14
 *
 * @copyright Copyright (C) 2022. Intellectual property of the author(s) listed
 * above.
 *
 */
#pragma once

#if __cplusplus >= 202000 || defined( __GNUG__ ) && __cplusplus == 201709
#    define HAS_CONCEPTS 1
#endif

#if !HAS_CONCEPTS
#    define CONCEPT_NAMESPACE
#    define CONCEPT_NAMESPACE_BEGIN
#    define CONCEPT_NAMESPACE_END
#else
#    define CONCEPT_NAMESPACE concepts::
#    define CONCEPT_NAMESPACE_BEGIN                                            \
        namespace concepts                                                     \
        {
#    define CONCEPT_NAMESPACE_END }
#endif

// all versions of C++ that we target use noexcept
#define NOEXCEPT noexcept

/**
 * @brief Single precision floating point. Certain tricks may be accelerated if
 * this happens to be IEEE-754 compliant and in binary format.
 * @note Generally speaking, Matrices using Single will be the fastest possible
 * but also using float introduces the most error so the results will be less
 * accurate. (It's infinitely precise since the same calculations will give the
 * exact same result every time, that's kind of the point of computers)
 */
typedef float       Single;
/**
 * @brief Double precision floating point. Certain tricks may be accelerated if
 * this happens to be IEEE-754 compliant and in binary format.
 * @note Generally speaking, Matrices using Double will be the best choice.
 * Doubles are in the best case as fast as Singles (if the compiler forgets
 * to optimize or the system lacks SIMD) and in the worst case half as fast if
 * both are implemented in hardware. However, with long matrix operations or
 * operations that involve large intermediate values relative to both the input
 * and output, Double can still significantly diverge from the exact value
 */
typedef double      Double;
/**
 * @brief Maximum precision floating point. The name "Triple" comes from it
 * being higher precision than "Double" and the word "Triple" having the same
 * number of letters as "Double". Certain tricks may still speed up operation if
 * Triple happens to IEEE-754 compliant and in binary format.
 * @note Generally, Triple provides the slowest operation and the most precise
 * results. Since there are only a finite number of bits in a Triple, the result
 * can still diverge from the exact value from long enough calculations or
 * calculations with significantly extreme intermediate values compared to their
 * outputs.
 * @note Generally, long double is implemented in software. This provides a
 * large speed penalty, however, sometimes it may be implemented in software.
 * This is sometimes the case on x86 / x64 where an 80-bit floating point is
 * available.
 *
 */
typedef long double Triple;