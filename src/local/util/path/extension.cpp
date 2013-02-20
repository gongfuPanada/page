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

#include <algorithm> // transform
#include <utility> // pair

#include <boost/filesystem/path.hpp>

#include "../functional/locale.hpp" // tolower_function

namespace page
{
	namespace util
	{
		boost::filesystem::path GetExtension(
			const boost::filesystem::path &path,
			unsigned index)
		{
			auto s(path.native());
			decltype(s)::size_type extStart, extEnd(s.npos);
			for (;;)
			{
				extStart = s.rfind('.', extEnd);
				if (!index || extStart == s.npos) break;
				extEnd = extStart;
				--index;
			}
			if (extStart)
			{
				auto ext(s.substr(extStart + 1, extEnd));
				std::transform(ext.begin(), ext.end(), ext.begin(), tolower_function<char>());
				return boost::filesystem::path(ext);
			}
			return boost::filesystem::path();
		}

		std::pair<boost::filesystem::path, boost::filesystem::path>
			PartitionExtension(const boost::filesystem::path &path)
		{
			auto s(path.native());
			auto i(s.rfind('.'));
			return i != s.npos ?
				std::make_pair(
					boost::filesystem::path(s.substr(0, i)),
					boost::filesystem::path(s.substr(i + 1))) :
				std::make_pair(
					path,
					boost::filesystem::path());
		}

		boost::filesystem::path AddExtension(
			const boost::filesystem::path &path,
			const boost::filesystem::path &extension)
		{
			boost::filesystem::path newPath(path);
			if (newPath.empty() || newPath.native().back() != '.')
				newPath += '.';
			newPath += extension;
			return newPath;
		}

		boost::filesystem::path WithExtension(
			const boost::filesystem::path &path,
			const boost::filesystem::path &extension)
		{
			if (GetExtension(path) != extension)
				return AddExtension(path, extension);
			return path;
		}
	}
}