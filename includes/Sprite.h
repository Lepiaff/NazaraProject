#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

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
			ar & boost::serialization::base_object<Renderable>(*this);
			ar & BOOST_SERIALIZATION_NVP(TEXTURE_NAME);
		}

	public:
		Sprite() = default;
		Sprite(std::string textureName) : NzP::Renderable("SPRITE"), TEXTURE_NAME(textureName) { ; }
		~Sprite() = default;

		virtual void UpdateGraphicsComponent(Ndk::GraphicsComponent& graphicsComponent)
		{
			Nz::SpriteRef sprite = Nz::ResourceManager<GraphicsSet, GraphicsSetParams>::Get(Nz::String(TEXTURE_NAME))->GetSprite(ID_SPRITE);

			graphicsComponent.Attach(sprite);
		}

	protected:

		//Variables sérialisables
		std::string TEXTURE_NAME;
		unsigned int ID_SPRITE;
	};
}
#endif