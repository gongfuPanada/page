/**
 * @section license
 *
 * Copyright (c) 2006-2013 David Osborn
 *
 * Permission is granted to use and redistribute this software in source and
 * binary form, with or without modification, subject to the following
 * conditions:
 *
 * 1. Redistributions in source form must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions, and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution, and in the same
 *    place and form as other copyright, license, and disclaimer information.
 *
 * As a special exception, distributions of derivative works in binary form may
 * include an acknowledgement in place of the above copyright notice, this list
 * of conditions, and the following disclaimer in the documentation and/or other
 * materials provided with the distribution, and in the same place and form as
 * other acknowledgements, similar in substance to the following:
 *
 *    Portions of this software are based on the work of David Osborn.
 *
 * This software is provided "as is", without any express or implied warranty.
 * In no event will the authors be liable for any damages arising out of the use
 * of this software.
 */

#ifndef    page_local_util_type_traits_sfinae_hpp
#   define page_local_util_type_traits_sfinae_hpp

#	include <type_traits> // enable_if, integral_constant, is_void

namespace page
{
	namespace util
	{
////////////////////////////////////////////////////////////////////////////////

	/**
	 * @defgroup ENABLE_IF
	 *
	 * A set of macros to simplify the most common uses of @c std::enable_if for
	 * SFINAE.
	 *
	 * @sa http://lists.boost.org/Archives/boost/2011/04/180192.php
	 *
	 * @{
	 */
	/**
	 * Applies SFINAE in the declaration of a function.
	 */
#	define ENABLE_IF(PREDICATE) \
		typename std::enable_if<PREDICATE>::type * = nullptr

	/**
	 * Applies SFINAE in the definition of a function.
	 */
#	define ENABLE_IF_IMPL(PREDICATE) \
		typename std::enable_if<PREDICATE>::type *

	/**
	 * Applies SFINAE in the return value of a function (whether it is a
	 * declaration or a definition).
	 */
#	define ENABLE_IF_RETURN(PREDICATE, RESULT) \
		typename std::enable_if<PREDICATE, RESULT>::type
	///@}

////////////////////////////////////////////////////////////////////////////////

	/**
	 * @defgroup DEFINE_SFINAE_TYPE_TRAIT
	 *
	 * A set of macros to make it easier to define new type-traits using SFINAE.
	 *
	 * @{
	 */
	/**
	 * Defines a one-parameter type-trait using SFINAE.
	 */
#	define DEFINE_SFINAE_TYPE_TRAIT_1(NAME, TEST) \
		template <typename> class NAME; \
		namespace detail \
		{ \
			template <typename A> struct NAME##_impl \
			{ \
				template <typename T> static void test(TEST *); \
				template <typename>   static int  test(...); \
				\
				static const bool value = std::is_void<decltype(test<A>(nullptr))>::value; \
			}; \
		} \
		template <typename T> struct NAME : \
			std::integral_constant<bool, detail::NAME##_impl<T>::value> {};

	/**
	 * Defines a two-parameter type-trait using SFINAE.
	 */
#	define DEFINE_SFINAE_TYPE_TRAIT_2(NAME, TEST) \
		template <typename, typename> class NAME; \
		namespace detail \
		{ \
			template <typename A, typename B> struct NAME##_impl \
			{ \
				template <typename T, typename U> static void test(TEST *); \
				template <typename,   typename>   static int  test(...); \
				\
				static const bool value = std::is_void<decltype(test<A, B>(nullptr))>::value; \
			}; \
		} \
		template <typename T, typename U> struct NAME : \
			std::integral_constant<bool, detail::NAME##_impl<T, U>::value> {};

	/**
	 * Defines a three-parameter type-trait using SFINAE.
	 */
#	define DEFINE_SFINAE_TYPE_TRAIT_3(NAME, TEST) \
		template <typename, typename, typename> class NAME; \
		namespace detail \
		{ \
			template <typename A, typename B, typename C> struct NAME##_impl \
			{ \
				template <typename T, typename U, typename V> static void test(TEST *); \
				template <typename,   typename,   typename>   static int  test(...); \
				\
				static const bool value = std::is_void<decltype(test<A, B, C>(nullptr))>::value; \
			}; \
		} \
		template <typename T, typename U, typename V> struct NAME : \
			std::integral_constant<bool, detail::NAME##_impl<T, U, V>::value> {};

	/**
	 * Defines a four-parameter type-trait using SFINAE.
	 */
#	define DEFINE_SFINAE_TYPE_TRAIT_4(NAME, TEST) \
		template <typename, typename, typename, typename> class NAME; \
		namespace detail \
		{ \
			template <typename A, typename B, typename C, typename D> struct NAME##_impl \
			{ \
				template <typename T, typename U, typename V, typename W> static void test(TEST *); \
				template <typename,   typename,   typename,   typename>   static int  test(...); \
				\
				static const bool value = std::is_void<decltype(test<A, B, C, D>(nullptr))>::value; \
			}; \
		} \
		template <typename T, typename U, typename V, typename W> struct NAME : \
			std::integral_constant<bool, detail::NAME##_impl<T, U, V, W>::value> {};
	///@}

////////////////////////////////////////////////////////////////////////////////

	/**
	 * @defgroup DEFINE_VARIADIC_SFINAE_TYPE_TRAIT
	 *
	 * A set of macros to make it easier to define new variadic type-traits
	 * using SFINAE.
	 *
	 * @{
	/**
	 * Defines a variadic one-parameter type-trait using SFINAE.
	 */
#	define DEFINE_VARIADIC_SFINAE_TYPE_TRAIT_1(NAME, TEST) \
		template <typename, typename...> class NAME; \
		namespace detail \
		{ \
			template <typename A, typename... B> struct NAME##_impl \
			{ \
				template <typename T, typename... U> static void test(TEST *); \
				template <typename,   typename...>   static int  test(...); \
				\
				static const bool value = std::is_void<decltype(test<A, B...>(nullptr))>::value; \
			}; \
		} \
		template <typename T, typename... U> struct NAME : \
			std::integral_constant<bool, detail::NAME##_impl<T, U...>::value> {};

	/**
	 * Defines a variadic two-parameter type-trait using SFINAE.
	 */
#	define DEFINE_VARIADIC_SFINAE_TYPE_TRAIT_2(NAME, TEST) \
		template <typename, typename, typename...> class NAME; \
		namespace detail \
		{ \
			template <typename A, typename B, typename... C> struct NAME##_impl \
			{ \
				template <typename T, typename U, typename... V> static void test(TEST *); \
				template <typename,   typename,   typename...>   static int  test(...); \
				\
				static const bool value = std::is_void<decltype(test<A, B, C...>(nullptr))>::value; \
			}; \
		} \
		template <typename T, typename U, typename... V> struct NAME : \
			std::integral_constant<bool, detail::NAME##_impl<T, U, V...>::value> {};
	///@}
	}
}

#endif
