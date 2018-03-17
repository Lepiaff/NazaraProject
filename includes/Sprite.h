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
#include "GraphicsSet.h"


namespace NzP
{
	class Sprite : public Renderable
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{///////////////////////////////////////////////////////////////////////////////////////////Au bout du 7/9ieme, ca crash !!!!!
			std::cout << "Serialize/Deserialize Sprite" << std::endl;

			std::cout << "Serialize/Deserialize Base Sprite : " << std::endl;
			ar & boost::serialization::base_object<Renderable>(*this);

			ar & TEXTURE_NAME;
			std::cout << "Sprite _ TEXTURE_NAME : " << TEXTURE_NAME << std::endl;
			ar & ID_SPRITE;
			std::cout << "Sprite _ ID_SPRITE : " << ID_SPRITE << std::endl;
			std::cout << "FIN Serialize/Deserialize Sprite " << std::endl;
		}

	public:
		Sprite() = default;
		Sprite(std::string textureName) : NzP::Renderable("SPRITE"), TEXTURE_NAME(textureName) { ; }
		~Sprite() = default;

		virtual void UpdateGraphicsComponent(Ndk::GraphicsComponent& graphicsComponent)
		{
			m_gSet = GSetManager::Get(TEXTURE_NAME);
			std::cout << "Nombre de reference pour " << TEXTURE_NAME << " = " << m_gSet->GetReferenceCount() << std::endl;
			std::cout << "Nombre de reference pour le sprite id " << ID_SPRITE << " = " << m_gSet->GetSprite(ID_SPRITE)->GetReferenceCount() << std::endl;
			graphicsComponent.Attach(m_gSet->GetSprite(ID_SPRITE));
		}

		void Save(const Nz::InstancedRenderableRef& renderable)
		{
			Nz::Sprite* spriteRef = dynamic_cast<Nz::Sprite*>(renderable.Get());
			Nz::Vector2f position{ 
				spriteRef->GetBoundingVolume().obb.localBox.x,
				spriteRef->GetBoundingVolume().obb.localBox.y };

			TEXTURE_NAME = renderable->GetMaterial()->GetFilePath().ToStdString();
			ID_SPRITE = GSetManager::Get(TEXTURE_NAME)->GetSpriteId(std::move(position));
		}

	private:

		//Variables sérialisables
		std::string TEXTURE_NAME;
		unsigned int ID_SPRITE;

		GraphicsSetRef m_gSet;
	};
}
#endif
