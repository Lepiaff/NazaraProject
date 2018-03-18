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
		{///////////////////////////////Au bout du 7/9ieme, ca crash !!!!!
			std::cout << "Serialize/Deserialize Sprite" << std::endl;
			ar & boost::serialization::base_object<Renderable>(*this);

			ar & m_textureName;
			std::cout << "Sprite _ m_textureName : " << m_textureName << std::endl;
			ar & m_idSprite;
			std::cout << "Sprite _ m_idSprite : " << m_idSprite << std::endl;
			std::cout << "FIN Serialize/Deserialize Sprite " << std::endl;
		}

	public:
		Sprite() = default;
		Sprite(std::string textureName) : NzP::Renderable("SPRITE"), m_textureName(textureName) { ; }
		~Sprite() {	std::cout << m_gSet->GetReferenceCount() << std::endl; }

		virtual void UpdateGraphicsComponent(Ndk::GraphicsComponent& graphicsComponent)
		{
			m_gSet = GSetManager::Get(m_textureName);
			graphicsComponent.Attach(m_gSet->GetSprite(m_idSprite));
		}

		void Save(const Nz::InstancedRenderableRef& renderable)
		{
			Nz::Sprite* spriteRef = dynamic_cast<Nz::Sprite*>(renderable.Get());
			Nz::Vector2f position{ 
				spriteRef->GetBoundingVolume().obb.localBox.x,
				spriteRef->GetBoundingVolume().obb.localBox.y };

			m_textureName = renderable->GetMaterial()->GetFilePath().ToStdString();
			m_idSprite = GSetManager::Get(m_textureName)->GetSpriteId(std::move(position));
		}

	private:

		//Variables sérialisables
		std::string m_textureName;
		unsigned int m_idSprite;

		GraphicsSetRef m_gSet;
	};
}
#endif
