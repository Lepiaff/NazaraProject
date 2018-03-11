#pragma once

#ifndef NODECOMPONENT_H
#define NODECOMPONENT_H


#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <NDK\Entity.hpp>
#include <NDK\Components.hpp>

#include "Component.h"

namespace NzP
{
	class NodeComponent : public Component
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			std::cout << "Serialize/Deserialize NodeComponent" << std::endl;

			std::cout << "Serialize/Deserialize Base NodeComponent : " << std::endl;
			BOOST_SERIALIZATION_BASE_OBJECT_NVP(Component);
			ar & BOOST_SERIALIZATION_NVP(POSITION);
			std::cout << "CollidableComponent _ POSITION : " << POSITION.first << " : " << POSITION.second << std::endl;
			ar & BOOST_SERIALIZATION_NVP(SCALE);
			std::cout << "CollidableComponent _ SCALE : " << SCALE.first << " : " << SCALE.second << std::endl;
			ar & BOOST_SERIALIZATION_NVP(ROTATION);
			std::cout << "CollidableComponent _ ROTATION : " << ROTATION << std::endl;
			std::cout << "FIN Serialize/Deserialize NodeComponent " << std::endl;
		}
	public:
		NodeComponent() : Component("NODE_COMPONENT") { ; }
		virtual ~NodeComponent() = default;

		virtual void UpdateEntity(Ndk::EntityHandle entity) const override
		{
			Ndk::NodeComponent& nodeComponent = entity->AddComponent<Ndk::NodeComponent>();
			nodeComponent.SetPosition(POSITION.first, POSITION.second);
			nodeComponent.SetScale(SCALE.first, SCALE.second, 0);
			nodeComponent.Rotate(Nz::EulerAnglesf(0.f, 0.f, ROTATION));
		}

		virtual void Save(Ndk::BaseComponent* comp) override
		{
			Ndk::NodeComponent* nodeComp = static_cast<Ndk::NodeComponent*>(comp);
			
			POSITION.first = nodeComp->GetPosition().x;
			POSITION.second = nodeComp->GetPosition().y;
			SCALE.first = nodeComp->GetScale().x;
			SCALE.second = nodeComp->GetScale().y;
			ROTATION = nodeComp->GetRotation().z;
		}

	protected:
		std::pair<float, float> POSITION;
		std::pair<float, float> SCALE;
		float ROTATION;
	};
}
#endif // !NODECOMPONENT_H
