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

#ifndef    page_local_util_class_Uncopyable_hpp
#   define page_local_util_class_Uncopyable_hpp

#	include "copy_move.hpp"

namespace page
{
	namespace util
	{
		/**
		 * Makes the derived class "uncopyable" (ISO/IEC n3242 8.4.3.3).
		 *
		 * @note It only makes sense to inherit from this class, as opposed to
		 *       using @c MAKE_UNCOPYABLE directly, when the derived class has
		 *       no "special member functions" that would prevent the compiler
		 *       from generating an implicit move-constructor, or when you also
		 *       want the derived class to be unmoveable.
		 */
		template <typename Derived>
			class Uncopyable
		{
			public:
			/**
			 * It is necessary to explicitly declare the default constructor
			 * because it will not be provided by default.
			 */
			Uncopyable() = default;

			MAKE_UNCOPYABLE(Uncopyable)
		};
	}
}

#endif
