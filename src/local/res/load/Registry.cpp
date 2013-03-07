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

#include <algorithm> // lower_bound

#include <boost/adaptors/indirected.hpp>

#include "../../err/Exception.hpp"
#include "../../util/path/extension.hpp" // GetExtension
#include "../node/Node.hpp"
#include "Registry.hpp"

namespace page { namespace res { namespace load {

////////// Record //////////////////////////////////////////////////////////////

	Record::Record(const Scanner &scanner, bool inspect, int priority) :
		scanner(scanner), inspect(inspect), priority(priority) {}

////////// Registry ////////////////////////////////////////////////////////////

	void Registry::Register(const std::type_info &type, const Record &record)
	{
		// function to compare record priority
		auto greaterPriority(
			std::bind(
				std::greater<decltype(Record::priority)>(),
				std::bind(
					util::make_member_of(&Record::priority),
					std::placeholders::_1),
				std::bind(
					util::make_member_of(&Record::priority),
					std::placeholders::_2)));

		// get type record for type
		auto &typeRecord(types.insert({type, {}}).first->second);

		// add record to list
		auto iter(
			records.insert(
				std::lower_bound(
					typeRecord.records.begin(),
					typeRecord.records.end(),
					record,
					greaterPriority),
				record));

		// associate extensions with record
		for (const auto &extension : record.extensions)
		{
			auto &records(typeRecord.extensions.insert({extension, {}}).first->second);
			records.insert(
				std::lower_bound(
					util::make_indirect_iterator(records.begin()),
					util::make_indirect_iterator(records.end()),
					record,
					greaterPriority).base(),
				iter);
		}

		// associate mime types with record
		for (const auto &mimeType : record.mimeTypes)
		{
			auto &records(typeRecord.mimeTypes.insert({extension, {}}).first->second);
			records.insert(
				std::lower_bound(
					util::make_indirect_iterator(records.begin()),
					util::make_indirect_iterator(records.end()),
					record,
					greaterPriority).base(),
				iter);
		}
	}

	const Loader &Registry::GetLoader(const std::type_info &type, const Node &node) const
	{
		auto iter(types.find(type));
		if (iter != types.end())
		{
			const auto &typeRecord(iter->second);

			// reset tried flag
			for (const auto &record : typeRecord.records)
				record.tried = false;

			// try loaders with matching mime type
			if (!node.mime.empty())
			{
				auto iter(typeRecord.mimeTypes.find(node.mime));
				if (iter != typeRecord.mimeTypes.end())
				{
					auto records(boost::adaptors::indirect(iter->second));
					for (const auto &record : records)
						if (record.inspect &&
							!record.tried &&
							(record.tried = true) &&
							record.checker(*node.pipe))
								return record.loader;

					THROW((err::Exception<err::ResModuleTag, err::NotFoundTag>("mismatched mime type") <<
						boost::errinfo_file_name(node.path) <<
						err::errinfo_subject(node.mime)))
				}
			}

			// try loaders with matching extension
			auto extension(util::GetExtension(node.path));
			if (!extension.empty())
			{
				auto iter(typeRecord.extensions.find(extension));
				if (iter != typeRecord.extensions.end())
				{
					auto records(boost::adaptors::indirect(iter->second));
					for (const auto &record : records)
						if (record.inspect &&
							!record.tried &&
							(record.tried = true) &&
							record.checker(*node.pipe))
								return record.loader;

					THROW((err::Exception<err::ResModuleTag, err::NotFoundTag>("mismatched extension") <<
						boost::errinfo_file_name(node.path) <<
						err::errinfo_subject(extension)))
				}
			}

			// try all remaining loaders
			if (node.inspect)
				for (const auto &record : typeRecord.records)
					if (record.inspect &&
						!record.tried &&
						(record.tried = true) &&
						record.checker(*node.pipe))
							return record.loader;
		}

		return nullptr;
	}

}}}
