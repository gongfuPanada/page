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

#include <windows.h>

#include "../../err/Exception.hpp"
#include "../../util/win32/string.hpp" // Native, String
#include "Console.hpp"

namespace page
{
	namespace wnd
	{
		namespace win32
		{
			Console::Console(const std::string &title)
			{
				if (!AllocConsole() || !SetConsoleTitle(util::win32::Native(title).c_str()))
					THROW((err::Exception<err::EnvModuleTag, err::Win32PlatformTag>("failed to allocate console") <<
						boost::errinfo_api_function("AllocConsole")))
			}

			void Console::Put(char c)
			{
				TCHAR tc = c;
				DWORD w;
				if (!WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), &tc, 1, &w, 0))
					THROW((err::Exception<err::EnvModuleTag, err::Win32PlatformTag>("failed to write to console") <<
						boost::errinfo_api_function("WriteConsole")))
			}
			void Console::Put(const std::string &s)
			{
				util::win32::String ts(util::win32::Native(s));
				DWORD w;
				if (!WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), ts.c_str(), ts.size(), &w, 0))
					THROW((err::Exception<err::EnvModuleTag, err::Win32PlatformTag>("failed to write to console") <<
						boost::errinfo_api_function("WriteConsole")))
			}
		}

		// factory function
		Console *MakeConsole(const std::string &title)
			{ return new win32::Console(title); }
	}
}