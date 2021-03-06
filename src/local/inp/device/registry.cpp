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

#include <cassert>
#include <iostream> // cout
#include <vector>

#include "../../log/Indenter.hpp"
#include "../Device.hpp" // Device::~Device
#include "registry.hpp" // DeviceFactory, Devices

namespace page
{
	namespace inp
	{
		namespace
		{
			struct Registry
			{
				struct Device
				{
					DeviceFactory factory;
					std::string name;
				};
				typedef std::vector<Device> Devices;
				Devices devices;
			};
			inline Registry &GetRegistry()
			{
				static Registry reg;
				return reg;
			}
		}

		// creation
		Devices MakeDevices(wnd::Window &wnd)
		{
			const Registry &reg(GetRegistry());
			Devices devices;
			for (Registry::Devices::const_iterator iter(reg.devices.begin()); iter != reg.devices.end(); ++iter)
			{
				std::cout << "loading device: " << iter->name << std::endl;
				log::Indenter indenter;
				Device *device = iter->factory(wnd);
				assert(device);
				devices.push_back(std::shared_ptr<Device>(device));
			}
			return devices;
		}

		// registration
		void RegisterDevice(const DeviceFactory &factory, const std::string &name)
		{
			assert(factory);
			Registry::Device device = {factory, name};
			GetRegistry().devices.push_back(device);
		}
	}
}
