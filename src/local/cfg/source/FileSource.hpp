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

#ifndef    page_local_cfg_source_FileSource_hpp
#   define page_local_cfg_source_FileSource_hpp

#	include <string>

#	include "Source.hpp"

namespace page { namespace cfg
{
	/**
	 * Represents a file containing configuration variables.
	 */
	class FileSource : public Source
	{
		/*--------------------------+
		| constructors & destructor |
		+--------------------------*/

		public:
		explicit FileSource(const std::string &);

		/*----------------------+
		| copy & move semantics |
		+----------------------*/

		MAKE_UNCOPYABLE(FileSource)

		/*----------------------+
		| Source implementation |
		+----------------------*/

		private:
		class Reader;
		class Writer;

		public:
		std::unique_ptr<Source::Reader> OpenReader() const override;
		std::unique_ptr<Source::Writer> OpenWriter() const override;

		/*-------------+
		| data members |
		+-------------*/

		private:
		std::string path;
	};
}}

#endif
