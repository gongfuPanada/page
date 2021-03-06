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

#include <cassert>

#include <GL/gl.h>

#include "ext.hpp" // ARB_multitexture
#include "get.hpp" // GetInteger

namespace page
{
	namespace vid
	{
		namespace opengl
		{
			namespace
			{
				bool reset = true;
			}

			// state
			GLenum GetActiveTexture()
			{
				assert(haveArbMultitexture);
				return GetInteger(GL_ACTIVE_TEXTURE_ARB);
			}
			unsigned GetActiveTextureIndex()
			{
				return GetActiveTexture() - GL_TEXTURE0_ARB;
			}
			bool CanAllocActiveTexture()
			{
				assert(haveArbMultitexture);
				return GetActiveTextureIndex() + !reset < GetInteger(GL_MAX_TEXTURE_UNITS_ARB);
			}

			// modifiers
			void AllocActiveTexture()
			{
				assert(haveArbMultitexture);
				assert(CanAllocActiveTexture());
				glActiveTextureARB(GetActiveTexture() + !reset);
				reset = false;
			}
			void ResetActiveTexture(GLenum activeTexture)
			{
				assert(haveArbMultitexture);
				glActiveTextureARB(activeTexture);
				reset = true;
			}
		}
	}
}
