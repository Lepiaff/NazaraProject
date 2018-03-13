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
			std::cout << "Serialize/Deserialize GraphicsComponent" << std::endl;

			std::cout << "Serialize/Deserialize Base GraphicsComponent : " << std::endl;
			ar & boost::serialization::base_object<Component>(*this);
			std::cout << "Serialize/Deserialize Sprite de GraphicsComponent " << std::endl;
			ar & SPRITE;
			std::cout << "FIN Serialize/Deserialize GraphicsComponent " << std::endl;
		}

		boost::shared_ptr<Sprite> SPRITE;

	public:
		GraphicsComponent() : Component("GRAPHICS_COMPONENT") { ; }
		virtual ~GraphicsComponent() = default;

		virtual void Save(Ndk::BaseComponent* comp) override
		{
			Ndk::GraphicsComponent* graphicsComp = dynamic_cast<Ndk::GraphicsComponent*>(comp);
			Ndk::GraphicsComponent::RenderableList renderablesList;
			graphicsComp->GetAttachedRenderables(&renderablesList);
			for (auto renderable : renderablesList)
			{
				Nz::Sprite* sprite = dynamic_cast<Nz::Sprite*>(renderable.Get());
				if (sprite)
				{
					std::unique_ptr<Sprite> sprite = std::make_unique<Sprite>();
					SPRITE = std::move(sprite);
					SPRITE->Save(renderable);
				}

				//idem pour le text ou autres renderables...
			}


		}

		virtual void UpdateEntity(Ndk::EntityHandle entity) const override
		{
			Ndk::GraphicsComponent& graphicsComponent = entity->AddComponent<Ndk::GraphicsComponent>();
			SPRITE->UpdateGraphicsComponent(graphicsComponent);
		}	
	};
}
#endif // !GRAPHICSCOMPONENT_H