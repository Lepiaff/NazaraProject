#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <Nazara/Graphics/Sprite.hpp>
#include <Nazara/Graphics/Material.hpp>
#include <Nazara/Core/ResourceManager.hpp>


#include "Renderable.h"
#include "GraphicsSetManager.h"
#include "GraphicsSet.h"


namespace NzP
{
	class Sprite : public NzP::Renderable
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			BOOST_SERIALIZATION_BASE_OBJECT_NVP(Renderable);
			ar & BOOST_SERIALIZATION_NVP(TEXTURE_NAME);
			ar & BOOST_SERIALIZATION_NVP(ID_SPRITE);
		}

	public:
		Sprite() = default;
		Sprite(std::string textureName) : NzP::Renderable("SPRITE"), TEXTURE_NAME(textureName) { ; }
		~Sprite() = default;

		virtual void UpdateGraphicsComponent(Ndk::GraphicsComponent& graphicsComponent)
		{
			if (GSetManager::Get(Nz::String(TEXTURE_NAME))->IsValid())
			{
				Nz::SpriteRef sprite = GSetManager::Get(Nz::String(TEXTURE_NAME))->GetSprite(ID_SPRITE);
				graphicsComponent.Attach(sprite);
			}	
		}

		void Save(const Nz::InstancedRenderableRef& renderable)
		{
			Nz::Rectf textureRect = dynamic_cast<Nz::Sprite*>(renderable.Get())->GetTextureCoords();
			TEXTURE_NAME = renderable->GetMaterial()->GetFilePath().ToStdString();
			ID_SPRITE = GSetManager::Get(TEXTURE_NAME)->GetSpriteId(textureRect);
		}

	protected:

		//Variables sérialisables
		std::string TEXTURE_NAME;
		unsigned int ID_SPRITE;
	};
}
#endif
