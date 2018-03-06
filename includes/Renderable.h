#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
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
			ar & BOOST_SERIALIZATION_NVP(RENDER_NAME);
		}

	public:
		Renderable() = default;
		Renderable(std::string name) : RENDER_NAME(std::move(name)) { ; }
		~Renderable() = default;

		virtual void UpdateGraphicsComponent(Ndk::GraphicsComponent& graphicsComponent) = 0;

	protected:
		std::string RENDER_NAME;
	};
}

//BOOST_CLASS_EXPORT_GUID(NzP::Sprite, "Sprite")