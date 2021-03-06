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

#ifndef    page_local_res_type_CameraSet_hpp
#   define page_local_res_type_CameraSet_hpp

#	include <string>
#	include <vector>

#	include "../../math/Quat.hpp"
#	include "../../math/Vector.hpp"

namespace page
{
	namespace res
	{
		struct CameraSet
		{
			struct Camera
			{
				std::string name;
				math::Vector<3> position;
				math::Quat<> orientation;
				float aspect;
				float fov; // degrees
				enum Tracking
				{
					noTracking,
					positionTracking,
					orientationTracking
				} tracking;
				float trackingDistance;
			};
			typedef std::vector<Camera> Cameras;
			Cameras cameras;
			struct TrackFace
			{
				typedef std::vector<Cameras::const_iterator> CameraPointers;
				CameraPointers cameras;
			};
			typedef std::vector<TrackFace> TrackFaces;
			TrackFaces trackFaces;
		};
	}
}

#endif
