#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <NDK\Entity.hpp>
#include <NDK\Components.hpp>

#include "Component.h"
#include "Sprite.h"
#include "Renderable.h"

namespace NzP
{
	class Renderable;
	class Sprite;

	class GraphicsComponent : public Component
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Component>(*this);
			ar & BOOST_SERIALIZATION_NVP(RENDER_TYPE);
			//ar.template register_type<Sprite>();
			//ar & BOOST_SERIALIZATION_NVP(RENDER_TYPE);
			
		}
	public:
		GraphicsComponent() : Component("GRAPHICS_COMPONENT") { ; }
		~GraphicsComponent() = default;

		virtual void update() { ; }
		virtual const std::string& Type() const { return TYPE; }
		virtual void UpdateEntity(Ndk::EntityHandle entity) const
		{
			Ndk::GraphicsComponent& graphicsComponent = entity->AddComponent<Ndk::GraphicsComponent>();
			RENDER_TYPE->UpdateGraphicsComponent(graphicsComponent);
		}

	protected:
		NzP::Renderable* RENDER_TYPE;
	};
}