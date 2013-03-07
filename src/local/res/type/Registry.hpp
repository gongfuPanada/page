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

#ifndef    page_local_res_type_Registry_hpp
#   define page_local_res_type_Registry_hpp

#	include <functional>
#	include <string>
#	include <typeindex>
#	include <typeinfo>
#	include <unordered_map>

#	include "../../util/class/Monostate.hpp"
#	include "../../util/gcc/init_priority.hpp" // REG_INIT_PRIORITY
#	include "../../util/memory/Deleter.hpp" // {,Default}Deleter

namespace page { namespace res { namespace type {

////////// PostLoader //////////////////////////////////////////////////////////

	/**
	 * A function object that is called after loading a type.
	 */
	class PostLoader
	{
		friend class Record;

		public:
		typedef void result_type;

		private:
		template <typename T>
			PostLoader(const std::function<void (T &)> &);

		public:
		template <typename T>
			void operator ()(T &) const;

		void operator ()(void *) const;

		operator bool() const;

		private:
		class Referenceable;
		std::function<void (Referenceable &)> f;
	};

////////// Record //////////////////////////////////////////////////////////////

	/**
	 * A data structure containing information about a type.
	 */
	struct Record
	{
		Record(
			std::string    const& name,
			PostLoader     const& postLoader,
			util::Deleter  const& deleter);

		/**
		 * The name of the type.
		 */
		std::string name;

		/**
		 * @copydoc PostLoader
		 */
		PostLoader postLoader;

		/**
		 * @copydoc util::Deleter
		 */
		util::Deleter deleter;
	};

////////// Registry ////////////////////////////////////////////////////////////

	/**
	 * A place for registering types.
	 */
	class Registry : public util::Monostate<Registry>
	{
		public:
		/**
		 * Registers a type.
		 */
		template <typename T>
			void Register(
				std::string                     const& name,
				std::function<void (T &)>       const& postLoader = nullptr,
				std::function<void (const T *)> const& deleter    = util::DefaultDeleter<T>());

		private:
		/**
		 * @copydoc Register
		 */
		void Register(const std::type_info &, const Record &);

		public:
		/**
		 * Returns the record associated with the specified type.
		 */
		template <typename T>
			const Record &Query() const;

		/**
		 * @copydoc Query
		 */
		const Record &Query(const std::type_info &) const;

		private:
		std::unordered_map<std::type_index, Record> records;
	};

////////////////////////////////////////////////////////////////////////////////

	/**
	 * Registers a type with @c Registry.
	 */
#	define REGISTER_TYPE(T, ...) \
		namespace \
		{ \
			struct Initializer() \
			{ \
				Initializer() \
				{ \
					GLOBAL(::page::res::type::Registry).Register<T>(__VA_ARGS__); \
				} \
			} initializer __attribute__((init_priority(REG_INIT_PRIORITY))); \
		}

}}}

#	include "Registry.tpp"
#endif