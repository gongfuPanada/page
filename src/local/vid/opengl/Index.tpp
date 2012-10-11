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

#include <iterator> // distance
#include "../../res/type/Mesh.hpp"

namespace page
{
	namespace vid
	{
		namespace opengl
		{
			template <typename OutputIterator> void InitIndices(OutputIterator iter, const res::Mesh &mesh)
			{
				for (res::Mesh::Faces::const_iterator meshFace(mesh.faces.begin()); meshFace != mesh.faces.end(); ++meshFace)
					for (res::Mesh::Face::VertexIndices::const_iterator meshVertex(meshFace->vertices.begin()); meshVertex != meshFace->vertices.end(); ++meshVertex)
						*iter++ = std::distance(mesh.vertices.begin(), *meshVertex);
			}
		}
	}
}