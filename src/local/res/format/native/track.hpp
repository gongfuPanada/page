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

#ifndef    page_local_res_format_native_track_hpp
#   define page_local_res_format_native_track_hpp

#	include <cstdint> // {,u}int32_t

namespace page { namespace res { namespace format
{
	namespace native { namespace track
	{
		const char sig[] = {'P', 'A', 'G', 'E', 't', 'r', 'a', 'c', 'k'};

#	pragma pack(push, 1)
		struct Header
		{
			std::uint32_t faces;
		};
		struct Face
		{
			float vertices[3][3];
			std::int32_t neighbours[3];
		};
#	pragma pack(pop)

		const char headerFormat[] = "d";
		const char faceFormat[] = "dddddddddddd";
	}}

	using namespace native::track;
}}}

#endif
