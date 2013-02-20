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

#ifndef    page_local_aud_openal_buffer_StreamBuffer_hpp
#   define page_local_aud_openal_buffer_StreamBuffer_hpp

#	include <array>
#	include <memory> // unique_ptr
#	include <vector>

#	include "../Buffer.hpp"

namespace page
{
	namespace res { class AudioStream; }

	namespace aud
	{
		namespace openal
		{
			struct StreamBuffer : Buffer
			{
				// construct/destroy
				StreamBuffer(ALuint source, const res::Sound &, bool loop, float playPosition);
				~StreamBuffer();

				// update
				void Update();

				private:
				// buffering
				void Queue(const ALuint *buffers, unsigned n);

				ALuint source;
				std::unique_ptr<res::AudioStream> stream;
				ALenum format;
				unsigned frequency;
				bool loop, end;
				typedef std::array<ALuint, 2> Buffers;
				Buffers buffers;
				typedef std::vector<char> BufferData;
				BufferData bufferData;
			};
		}
	}
}

#endif
