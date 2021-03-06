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

#include "ext.hpp" // EXT_framebuffer_object
#include "get.hpp" // Get{Boolean,Integer}
#include "RenderTargetSaver.hpp"

namespace page
{
	namespace vid
	{
		namespace opengl
		{
			// construct
			RenderTargetSaver::RenderTargetSaver(bool enabled)
			{
				Reset(enabled);
			}

			// modifiers
			void RenderTargetSaver::Save()
			{
				if (haveExtFramebufferObject)
					framebuffer = GetInteger(GL_FRAMEBUFFER_BINDING_EXT);
				drawBuffer = GetInteger(GL_DRAW_BUFFER);
				glGetIntegerv(GL_SCISSOR_BOX, scissorBox);
				glGetIntegerv(GL_VIEWPORT, viewport);
			}
			void RenderTargetSaver::Load()
			{
				if (haveExtFramebufferObject)
					glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
				glDrawBuffer(drawBuffer);
				glViewport(
					viewport[0], viewport[1],
					viewport[2], viewport[3]);
				glScissor(
					scissorBox[0], scissorBox[1],
					scissorBox[2], scissorBox[3]);
			}
		}
	}
}
