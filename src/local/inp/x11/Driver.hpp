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

#ifndef    page_local_inp_x11_Driver_hpp
#   define page_local_inp_x11_Driver_hpp

#	include <X11/Xlib.h> // KeySym, Time, XEvent

#	include "../Driver.hpp"

namespace page
{
	namespace inp
	{
		namespace x11
		{
			struct Driver : inp::Driver
			{
				// construct
				explicit Driver(wnd::x11::Window &);

				// window access
				wnd::x11::Window &GetWindow();
				const wnd::x11::Window &GetWindow() const;

				private:
				// state query
				State Poll() const;

				// cursor mode modifiers
				void DoSetCursorMode(CursorMode);

				// system cursor state
				math::Vector<2, unsigned> GetRawCursorPosition() const;

				// window signal handlers
				void OnEvent(const XEvent &);
				boost::signals::scoped_connection eventCon;

				// key state
				bool IsKeyDown(KeySym, const char keys[32]) const;

				// cursor state
				struct
				{
					math::Vector<2, unsigned> pointPosition;
				} cursor;
			};
		}
	}
}

#endif
