#pragma once

#ifndef COLLIDABLECOMPONENT_H
#define COLLIDABLECOMPONENT_H

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <NDK\Entity.hpp>
#include <NDK\Components.hpp>

#include "Component.h"

namespace NzP
{
	class CollidableComponent : public Component
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			std::cout << "Serialize/Deserialize CollidableComponent" << std::endl;

			ar & boost::serialization::base_object<Component>(*this);
			ar & m_position;
			std::cout << "CollidableComponent _ POSITION : " << m_position << std::endl;
			ar & m_taille;
			std::cout << "CollidableComponent _ TAILLE : " << m_taille << std::endl;
			std::cout << "FIN Serialize/Deserialize CollidableComponent " << std::endl;
		}
	public:
		CollidableComponent() : Component("COLLIDABLE_COMPONENT") { ; }
		virtual ~CollidableComponent() = default;

		virtual void UpdateNazaraEntity(Ndk::EntityHandle entity) const override
		{
			Ndk::CollisionComponent2D& collisionComponent = 
				entity->AddComponent<Ndk::CollisionComponent2D>();
		}

		virtual void Save(Ndk::BaseComponent* comp) override
		{

		}

	protected:
		unsigned int m_position[2];
		unsigned int m_taille[2];
	};
}
#endif // !COLLIDABLECOMPONENT_H
