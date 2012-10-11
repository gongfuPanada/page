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

#include <cassert>
#include <memory> // unique_ptr
#include "../../Pipe.hpp" // Pipe::Open
#include "../../pipe/EndianPipe.hpp"
#include "../../Stream.hpp" // Stream::{~Stream,ReadSome,Seek}
#include "AudioStream.hpp"
#include "PcmDecoder.hpp"

namespace page
{
	namespace res
	{
		namespace
		{
			struct PcmStream : AudioStream
			{
				// construct
				PcmStream(const Pipe &, unsigned sampleSize);

				// operations
				unsigned Read(void *, unsigned);
				void Seek(unsigned sample);

				private:
				std::unique_ptr<Stream> super;
				unsigned sampleSize;
			};

			// construct
			PcmStream::PcmStream(const Pipe &pipe, unsigned sampleSize) :
				super(pipe.Open()), sampleSize(sampleSize) {}

			// operations
			unsigned PcmStream::Read(void *s, unsigned n)
			{
				return super->ReadSome(s, n);
			}
			void PcmStream::Seek(unsigned sample)
			{
				super->Seek(sample * sampleSize);
			}
		}

		// construct
		PcmDecoder::PcmDecoder(const std::shared_ptr<const Pipe> &pipe, unsigned channels, unsigned bitDepth, util::Endian endian) :
			pipe(pipe), sampleSize(channels * bitDepth / 8)
		{
			assert(pipe);
			if (endian != util::nativeEndian)
				switch (bitDepth)
				{
					case 8: break;
					case 16: this->pipe.reset(new EndianPipe(pipe, "w", endian)); break;
					case 24: this->pipe.reset(new EndianPipe(pipe, "t", endian)); break;
					case 32: this->pipe.reset(new EndianPipe(pipe, "d", endian)); break;
					case 48: this->pipe.reset(new EndianPipe(pipe, "T", endian)); break;
					case 64: this->pipe.reset(new EndianPipe(pipe, "q", endian)); break;
					default: assert(!"unsupported bit depth");
				}
		}

		// operations
		AudioStream *PcmDecoder::Open() const
		{
			return new PcmStream(*pipe, sampleSize);
		}
	}
}