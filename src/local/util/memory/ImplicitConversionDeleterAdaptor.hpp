/**
 * @section license
 *
 * Copyright (c) 2006-2012 David Osborn
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

#ifndef    page_local_util_memory_ImplicitConversionDeleterAdaptor_hpp
#   define page_local_util_memory_ImplicitConversionDeleterAdaptor_hpp

#	include <functional> // function

#	include "../algorithm/downcast.hpp"

namespace page { namespace util
{
	/**
	 * An adaptor for deleters to support implicit pointer conversion, such as
	 * derived-to-base-pointer conversion.
	 */
	template <typename T, typename U>
		struct ImplicitConversionDeleterAdaptor
	{
		typedef void result_type;
		typedef const T *argument_type;

		private:
		typedef std::function<void (const U *)> deleter_type;

		public:
		explicit ImplicitConversionDeleterAdaptor(const deleter_type &deleter) :
			deleter(deleter) {}

		void operator ()(const T *x) const
		{
			return deleter(&downcast<const U &>(*x));
		}

		private:
		deleter_type deleter;
	};
}}

#endif
