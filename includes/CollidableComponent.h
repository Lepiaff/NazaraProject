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
			BOOST_SERIALIZATION_BASE_OBJECT_NVP(Component);
			ar & BOOST_SERIALIZATION_NVP(POSITION);
			ar & BOOST_SERIALIZATION_NVP(TAILLE);
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
