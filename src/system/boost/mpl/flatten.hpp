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

#ifndef    page_system_boost_mpl_flatten_hpp
#   define page_system_boost_mpl_flatten_hpp

#	include <boost/mpl/begin_end.hpp> // end
#	include <boost/mpl/clear.hpp>
#	include <boost/mpl/inserter.hpp>
#	include <boost/mpl/insert_range.hpp>
#	include <boost/mpl/is_sequence.hpp>
#	include <boost/mpl/quote.hpp>
#	include <boost/mpl/single_view.hpp>
#	include <boost/mpl/transform.hpp>

namespace boost
{
	namespace mpl
	{
		/**
		 * Recursively expands sub-sequences to produce a flat sequence.
		 */
		template <
			typename Sequence,
			bool = is_sequence<Sequence>::value>
				struct flatten
		{
			typedef
				typename transform<
					Sequence,
					quote1<flatten>,
					inserter<
						typename clear<Sequence>::type,
						insert_range<_1, end<_1>, _2>>
					>::type type;
		};

		template <typename T>
			struct flatten<T, false>
		{
			typedef single_view<T> type;
		};
	}
}

#endif
