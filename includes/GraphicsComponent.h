#pragma once

#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H


#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/unique_ptr.hpp>

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
			BOOST_SERIALIZATION_BASE_OBJECT_NVP(Component);
			ar & BOOST_SERIALIZATION_NVP(RENDER_TYPE);	
		}


		/*friend class boost::serialization::access;
		template<class Archive>
		void save(Archive& ar, const unsigned int version) const
		{
			BOOST_SERIALIZATION_BASE_OBJECT_NVP(Component);
			ar & BOOST_SERIALIZATION_NVP(RENDER_TYPE);
		}

		template<class Archive>
		void load(Archive& ar, const unsigned int version)
		{
			BOOST_SERIALIZATION_BASE_OBJECT_NVP(Component);
			ar & BOOST_SERIALIZATION_NVP(RENDER_TYPE);
			BOOST_SERIALIZATION_BASE_OBJECT_NVP(Component);
			Sprite* sprite;
			ar & boost::serialization::make_nvp("SPRITE", sprite);
			if (sprite) { RENDER_TYPE = boost::make_shared<Sprite>(*sprite); }
		}
		BOOST_SERIALIZATION_SPLIT_MEMBER()*/
	public:
		GraphicsComponent() : Component("GRAPHICS_COMPONENT") { ; }
		virtual ~GraphicsComponent() = default;

		virtual void Save(Ndk::BaseComponent* comp) override
		{
			/*Ndk::GraphicsComponent* graphicsComp = dynamic_cast<Ndk::GraphicsComponent*>(comp);
			Ndk::GraphicsComponent::RenderableList renderablesList;
			graphicsComp->GetAttachedRenderables(&renderablesList);
			for (auto renderable : renderablesList)
			{
				Nz::Sprite* sprite = dynamic_cast<Nz::Sprite*>(renderable.Get());
				if (sprite)
				{
					std::unique_ptr<Sprite> sprite = std::make_unique<Sprite>();
					RENDER_TYPE = std::move(sprite);
					RENDER_TYPE->Save(renderable);
				}

				//idem pour le text ou autres renderables...
			}*/
		}

		virtual void UpdateEntity(Ndk::EntityHandle entity) const override
		{
			/*Ndk::GraphicsComponent& graphicsComponent = entity->AddComponent<Ndk::GraphicsComponent>();
			RENDER_TYPE->UpdateGraphicsComponent(graphicsComponent);*/
		}

	protected:
		boost::shared_ptr<NzP::Renderable> RENDER_TYPE;
	};
}
#endif // !GRAPHICSCOMPONENT_H