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

#ifndef    page_local_aud_Channel_hpp
#   define page_local_aud_Channel_hpp

namespace page { namespace aud
{
	struct Channel
	{
		// construct/destroy
		// NOTE: use fade when emerging from occlusion
		explicit Channel(bool fade);
		virtual ~Channel();

		// update
		void Update(float deltaTime);

		protected:
		// state
		float GetVolume() const;
		float GetLinearVolume() const;

		private:
		// state
		virtual float DoGetLinearVolume() const = 0;

		// update
		virtual void DoUpdate(float deltaTime) = 0;
		virtual void DoUpdate2() = 0;

		bool playing;
		float level;

		protected:
		static const float fadeExponent;
	};
}}

#endif
