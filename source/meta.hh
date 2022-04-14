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
#endif