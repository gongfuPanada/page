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

#include <algorithm> // reverse

#include "endian.hpp" // Endian

namespace page
{
	namespace util
	{
		namespace
		{
			void Switch(void *data, unsigned size)
			{
				std::reverse(
					static_cast<unsigned char *>(data),
					static_cast<unsigned char *>(data) + size);
			}
			unsigned Transform(void *data, const std::string &fmt)
			{
				char *ptr = static_cast<char *>(data);
				for (std::string::const_iterator unit(fmt.begin()); unit != fmt.end(); ++unit)
				{
					unsigned size;
					switch (*unit)
					{
						case 'b': size = 1; break; // byte
						case 'w': size = 2; break; // word
						case 't': size = 3; break; // tbyte
						case 'd': size = 4; break; // dword
						case 'T': size = 6; break; // tword
						case 'q': size = 8; break; // qword
					}
					Switch(ptr, size);
					ptr += size;
				}
				return ptr - static_cast<char *>(data);
			}
		}

		void SwitchEndian(void *data, unsigned size, Endian src, Endian dest)
		{
			if (src != dest) Switch(data, size);
		}
		void TransformEndian(void *data, const std::string &fmt, Endian src, Endian dest)
		{
			if (src != dest) Transform(data, fmt);
		}
		void TransformEndianArray(void *data, unsigned n, const std::string &fmt, Endian src, Endian dest)
		{
			if (src == dest) return;
			for (unsigned i = 0; i < n; ++i)
				data = static_cast<char *>(data) + Transform(data, fmt);
		}
	}
}
