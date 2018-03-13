#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <NDK\Components.hpp>

namespace NzP
{
	class Renderable
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			std::cout << "Serialize/Deserialize Renderable" << std::endl;
			ar & RENDER_NAME;
			std::cout << "Renderable _ RENDER_NAME : " << RENDER_NAME << std::endl;
		}

	public:
		Renderable() = default;
		Renderable(std::string name) : RENDER_NAME(std::move(name)) { ; }
		~Renderable() = default;

		virtual void UpdateGraphicsComponent(Ndk::GraphicsComponent& graphicsComponent) = 0;
		virtual void Save(const Nz::InstancedRenderableRef& renderable) = 0;

	protected:
		std::string RENDER_NAME;
	};
}