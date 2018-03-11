#pragma once

#ifndef COLLIDABLECOMPONENT_H
#define COLLIDABLECOMPONENT_H

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/archive/xml_oarchive.hpp>
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

			std::cout << "Serialize/Deserialize Base CollidableComponent : " << std::endl;
			BOOST_SERIALIZATION_BASE_OBJECT_NVP(Component);
			ar & BOOST_SERIALIZATION_NVP(POSITION);
			std::cout << "CollidableComponent _ POSITION : " << POSITION << std::endl;
			ar & BOOST_SERIALIZATION_NVP(TAILLE);
			std::cout << "CollidableComponent _ TAILLE : " << TAILLE << std::endl;
			std::cout << "FIN Serialize/Deserialize CollidableComponent " << std::endl;
		}
	public:
		CollidableComponent() : Component("COLLIDABLE_COMPONENT") { ; }
		virtual ~CollidableComponent() = default;

		virtual void UpdateEntity(Ndk::EntityHandle entity) const override
		{
			Ndk::CollisionComponent2D& collisionComponent = entity->AddComponent<Ndk::CollisionComponent2D>();
			
		}

		virtual void Save(Ndk::BaseComponent* comp) override
		{

		}

	protected:
		unsigned int POSITION[2];
		unsigned int TAILLE[2];
	};
}
#endif // !COLLIDABLECOMPONENT_H
