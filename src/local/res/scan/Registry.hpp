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

#ifndef    page_local_res_scan_Registry_hpp
#   define page_local_res_scan_Registry_hpp

#	include <forward_list>
#	include <functional> // function
#	include <memory> // shared_ptr
#	include <string>
#	include <unordered_map>

#	include "../../util/class/Monostate.hpp"
#	include "../../util/gcc/init_priority.hpp" // REG_INIT_PRIORITY

namespace page { namespace res { class Node; class Pipe; }}

namespace page { namespace res { namespace scan {

	/**
	 * A function object that is called by a scanner when it has found a node.
	 */
	using ScanCallback = std::function<void (const Node &)>;

	/**
	 * A function object that forms the implementation of a scanner.
	 *
	 * @return @c true if the scanner found a node.
	 */
	using Scanner = std::function<
		bool (const std::shared_ptr<const Pipe> &, const ScanCallback &)>;

////////// Record //////////////////////////////////////////////////////////////

	/**
	 * A data structure containing information about a scanner.
	 */
	struct Record
	{
		/**
		 * Permits Registry to access tried.
		 */
		friend class Registry;

		Record(
			std::string              const& name,
			Scanner                  const& scanner,
			std::vector<std::string> const& extensions = {},
			std::vector<std::string> const& mimeTypes  = {},
			bool                            inspect    = true,
			int                             priority   = 0);

		/**
		 * The name of the scanner.
		 */
		std::string name;

		/**
		 * @copydoc Scanner
		 */
		Scanner scanner;

		/**
		 * The extensions that this scanner recognizes.
		 */
		std::vector<std::string> extensions;

		/**
		 * The mime types that this scanner recognizes.
		 */
		std::vector<std::string> mimeTypes;

		/**
		 * @c true if this scanner should be tried as a final resort, even if
		 * none of its extensions or mime types match the node.
		 */
		bool inspect;

		/**
		 * A higher priority means that this scanner will be tried before other
		 * scanners of the same level with a lower priority.
		 */
		int priority;

		private:
		/**
		 * A marker used when scanning, which will be @c true if this scanner
		 * has already been tried.
		 *
		 * @note This member has no definite value outside @c Registry::Scan.
		 */
		bool mutable tried;
	};

////////// Registry ////////////////////////////////////////////////////////////

	/**
	 * A place for registering scanners.
	 */
	class Registry : public util::Monostate<Registry>
	{
		public:
		/**
		 * Registers a scanner.
		 */
		template <typename... RecordArgs>
			void Register(RecordArgs &&...);

		private:
		/**
		 * @copydoc Register
		 */
		void Register(const Record &);

		/**
		 * Searches for a scanner that is compatible with the given node and
		 * calls it with the provided callback.
		 *
		 * @return @c true if any of the scanners found a node.
		 */
		bool Scan(const Node &, const ScanCallback &) const;

		private:
		std::forward_list<Record> records;
		std::unordered_map<std::string, std::forward_list<typename decltype(records)::const_iterator>> extensions;
		std::unordered_map<std::string, std::forward_list<typename decltype(records)::const_iterator>> mimeTypes;

		static const unsigned lockSize;
	};

////////////////////////////////////////////////////////////////////////////////

	/**
	 * Registers a scanner with @c Registry.
	 */
#	define REGISTER_SCANNER(...) \
		namespace \
		{ \
			struct Initializer() \
			{ \
				Initializer() \
				{ \
					GLOBAL(::page::res::scan::Registry).Register(__VA_ARGS__); \
				} \
			} initializer __attribute__((init_priority(REG_INIT_PRIORITY))); \
		}

}}}

#	include "Registry.tpp"
#endif
