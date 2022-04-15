/**
 * @file meta.hh
 * @author Joshua Buchanan (joshuarobertbuchanan@gmail.com)
 * @brief Metaprogramming thingies
 * @version 1
 * @date 2022-04-14
 *
 * @copyright Copyright (C) 2022. Intellectual property of the author(s) listed above.
 *
 */
#pragma once

#if __cplusplus >= 202000 || defined(__GNUG__) && __cplusplus == 201709
#define HAS_CONCEPTS 1
#endif

#if !HAS_CONCEPTS
#define CONCEPT_NAMESPACE
#define CONCEPT_NAMESPACE_BEGIN
#define CONCEPT_NAMESPACE_END
#else
#define CONCEPT_NAMESPACE concepts::
#define CONCEPT_NAMESPACE_BEGIN \
    namespace concepts          \
    {
#define CONCEPT_NAMESPACE_END }
#endif

#if __cplusplus < 201700
#define NOEXCEPT throw()
#else
#define NOEXCEPT noexcept

// single precision
typedef float Single;
// double precision
typedef double Double;
// highest precision. "Triple" has the same number of characters as "Double" and
// "Single" Generally, "Triple" is not going to be "Triple" precision. On x86
// Triple is either 80-bits or 128-bits (x87 Real or Quadruple precision).
typedef long double Triple;

#endif