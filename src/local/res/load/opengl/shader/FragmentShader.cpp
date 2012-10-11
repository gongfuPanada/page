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
#include <memory> // shared_ptr
#include <GL/gl.h> // glext.h
#include <GL/glext.h> // GL_FRAGMENT_SHADER_ARB
#include "../../../../util/scoped_ptr.hpp"
#include "../../../Pipe.hpp" // Pipe::Open
#include "../../../Stream.hpp" // Stream::GetText
#include "../../../type/opengl/Shader.hpp"
#include "../../register.hpp" // LoadFunction, REGISTER_LOADER

namespace page
{
	namespace res
	{
		namespace opengl
		{
			Shader *LoadFragmentShader(const std::shared_ptr<const Pipe> &pipe)
			{
				assert(pipe);
				util::scoped_ptr<Stream> stream(pipe->Open());
				util::scoped_ptr<Shader> shader(new Shader);
				shader->type = GL_FRAGMENT_SHADER_ARB;
				shader->source = stream->GetText();
				return shader.release();
			}

			LoadFunction GetFragmentShaderLoader(const Pipe &pipe)
			{
				return LoadFragmentShader;
			}

			REGISTER_LOADER(Shader, GetFragmentShaderLoader,
				"fs", "", "", false)
		}
	}
}