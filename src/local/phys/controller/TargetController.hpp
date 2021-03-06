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

// interpolated frame matching controller
// similar attributes should be defined in each frame to avoid popping

#ifndef    page_local_phys_controller_TargetController_hpp
#   define page_local_phys_controller_TargetController_hpp

#	include <vector>

#	include "../Controller.hpp"

namespace page { namespace phys
{
	class TargetController : public Controller
	{
		public:
		// construct
		explicit TargetController(Layer, float fadeDuration = 1);

		protected:
		// modifiers
		void SetTarget(const Frame &);
		void SetTarget(const Frame &, float fadeDuration);

		private:
		// update hooks
		virtual void UpdateTargets(float deltaTime) = 0;

		// update/generate frame
		void DoUpdate(float deltaTime);
		Frame DoGetFrame(const Frame &, const Frame &) const;

		float fadeDuration;
		struct Target
		{
			Frame frame;
			float opacity, fadeDuration;
		};
		typedef std::vector<Target> Targets;
		Targets targets;
	};
}}

#endif
