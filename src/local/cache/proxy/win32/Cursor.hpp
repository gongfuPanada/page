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

#ifndef    page_local_cache_proxy_win32_Cursor_hpp
#   define page_local_cache_proxy_win32_Cursor_hpp

#	include <windows.h> // HCURSOR

#	include "../../../util/raii/copy_ptr.hpp"
#	include "../Proxy.hpp"

namespace page { namespace res { class Cursor; }}

namespace page { namespace cache { namespace win32
{
	/**
	 * A proxy representing a cursor in the cache.
	 */
	class Cursor :
		public Proxy<HCURSOR>,
		public virtual util::Cloneable<Cursor, Proxy<HCURSOR>>
	{
		/*------+
		| types |
		+------*/

		public:
		typedef typename Proxy<HCURSOR>::Instance Instance;

		/*--------------------------+
		| constructors & destructor |
		+--------------------------*/

		public:
		explicit Cursor(const Proxy<res::Cursor> &, unsigned size);

		/*----------+
		| observers |
		+----------*/

		public:
		std::string GetType() const override;
		std::string GetSource() const override;
		operator bool() const override;

		/*--------------+
		| instantiation |
		+--------------*/

		private:
		Instance Make() const override;

		/*-------------+
		| data members |
		+-------------*/

		private:
		util::copy_ptr<Proxy<res::Cursor>> cursor;
		unsigned size;
	};
}}}

#endif
