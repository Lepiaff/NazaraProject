#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/archive/xml_oarchive.hpp>

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
			ar & boost::serialization::base_object<Component>(*this);
			ar & BOOST_SERIALIZATION_NVP(POSITION_X);
			ar & BOOST_SERIALIZATION_NVP(POSITION_y);
			ar & BOOST_SERIALIZATION_NVP(TAILLE_X);
			ar & BOOST_SERIALIZATION_NVP(TAILLE_Y);
		}
	public:
		CollidableComponent() : Component("COLLIDABLE_COMPONENT") { ; }
		~CollidableComponent() = default;

		virtual void update() { ; }

		virtual void UpdateEntity(Ndk::EntityHandle entity) const
		{
			Ndk::CollisionComponent2D& collisionComponent = entity->AddComponent<Ndk::CollisionComponent2D>();
			
		}

	protected:
		unsigned int POSITION_X;
		unsigned int POSITION_y;
		unsigned int TAILLE_X;
		unsigned int TAILLE_Y;
	};
}