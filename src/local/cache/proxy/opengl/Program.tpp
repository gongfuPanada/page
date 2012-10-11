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

#include <algorithm> // transform
#include <functional> // mem_fun_ref
#include <iterator> // back_inserter

namespace page
{
	namespace cache
	{
		namespace opengl
		{
			// construct
			template <typename InputIterator> Program::Program(InputIterator first, InputIterator last, typename std::enable_if<util::is_iterator_over<InputIterator, Proxy<res::opengl::Shader>>::value>::type *)
			{
				std::transform(first, last, std::back_inserter(shaders),
					std::mem_fun_ref(&Proxy<res::opengl::Shader>::Copy));
				PostInit();
			}
		}
	}
}