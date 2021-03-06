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

#ifndef    page_local_log_stream_BranchableStream_hpp
#   define page_local_log_stream_BranchableStream_hpp

#	include <memory> // shared_ptr
#	include <vector>

#	include "Stream.hpp"

namespace page
{
	namespace log
	{
		/**
		 * A stream which can have other streams attached (referred to as
		 * branches), and which will pass any data written to it onto those
		 * streams.
		 */
		class BranchableStream : public Stream
		{
			/*--------------------------+
			| constructors & destructor |
			+--------------------------*/

			public:
			/**
			 * Construct an instance with any number of branches.
			 */
			template <typename... Branches>
				explicit BranchableStream(Branches &&...);

			/*----------+
			| branching |
			+----------*/

			public:
			/**
			 * Attach a stream as a new branch.
			 */
			void Attach(const std::shared_ptr<Stream> &);

			/**
			 * Remove all branches.
			 */
			void Detach();

			/**
			 * Attach all of the branches from another @c BranchableStream.
			 */
			void Extend(const BranchableStream &);

			/*----------------------+
			| Stream implementation |
			+----------------------*/

			protected:
			void DoWrite(const std::string &) override;
			void DoFlush() override;
			void DoClear() override;

			/*-------------+
			| data members |
			+-------------*/

			private:
			std::vector<std::shared_ptr<Stream>> branches;
		};
	}
}

#	include "BranchableStream.tpp"
#endif
