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

#ifndef    page_local_cache_proxy_opengl_Texture_hpp
#   define page_local_cache_proxy_opengl_Texture_hpp

#	include "../../../math/Vector.hpp"
#	include "../../../util/raii/copy_ptr.hpp"
#	include "../../../vid/opengl/TextureFlags.hpp"
#	include "../../../vid/opengl/TextureFormat.hpp"
#	include "../Proxy.hpp"

namespace page
{
	namespace res { class Image; }
	namespace vid { namespace opengl { class Texture; }}
}

namespace page { namespace cache { namespace opengl
{
	/**
	 * A proxy representing a texture in the cache.
	 */
	class Texture :
		public Proxy<vid::opengl::Texture>,
		public virtual util::Cloneable<Texture, Proxy<vid::opengl::Texture>>
	{
		/*------+
		| types |
		+------*/

		public:
		typedef typename Proxy<vid::opengl::Texture>::Instance Instance;

		/*--------------------------+
		| constructors & destructor |
		+--------------------------*/

		public:
		explicit Texture(const Proxy<res::Image> &,
			vid::opengl::TextureFormat = vid::opengl::defaultTextureFormat,
			vid::opengl::TextureFlags =
				static_cast<vid::opengl::TextureFlags>(
					vid::opengl::filterTextureFlag |
					vid::opengl::mipmapTextureFlag),
			const math::Vector<2, bool> &clamp = false);

		/*----------+
		| observers |
		+----------*/

		public:
		std::string GetType() const override;
		std::string GetSource() const override;
		operator bool() const override;

		/*--------------+
		| instantiation |
		+--------------*/

		private:
		Instance Make() const override;

		/*-------------+
		| data members |
		+-------------*/

		private:
		util::copy_ptr<Proxy<res::Image>> image;
		vid::opengl::TextureFormat format;
		vid::opengl::TextureFlags flags;
		math::Vector<2, bool> clamp;
	};
}}}

#endif
