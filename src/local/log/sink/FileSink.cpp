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

#include "../../cfg/State.hpp" // State::{GetGlobalInstance,installPath}
#include "../../err/Exception.hpp"
#include "FileSink.hpp"

namespace page
{
	namespace log
	{
		/*--------------------------+
		| constructors & destructor |
		+--------------------------*/

		FileSink::FileSink(const boost::filesystem::path &path)
		{
			auto absPath = absolute(path, *cfg::State::GetGlobalInstance().installPath);
			fs.open(absPath.string());
			if (!fs)
			{
				BOOST_THROW_EXCEPTION(
					err::FileException("failed to open file stream") <<
					boost::errinfo_api_function("std::ofstream::open") <<
					boost::errinfo_file_name(absPath.string()) <<
					boost::errinfo_file_open_mode("w"));
			}
		}

		/*----------------------+
		| Stream implementation |
		+----------------------*/

		void FileSink::DoWrite(const std::string &s)
		{
			if (!fs.write(s.data(), s.size()))
				BOOST_THROW_EXCEPTION(err::FileException("file write error"));
		}
	}
}