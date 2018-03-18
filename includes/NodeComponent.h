#pragma once

#ifndef NODECOMPONENT_H
#define NODECOMPONENT_H


#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/serialization.hpp>
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
			ar & m_position;
			std::cout << "NodeComponent _ m_position : " << m_position.first << " : " << m_position.second << std::endl;
			ar & m_scale;
			std::cout << "NodeComponent _ m_scale : " << m_scale.first << " : " << m_scale.second << std::endl;
			ar & m_rotation;
			std::cout << "NodeComponent _ m_rotation : " << m_rotation << std::endl;
			std::cout << "FIN Serialize/Deserialize NodeComponent " << std::endl;
		}
	public:
		NodeComponent() = default;
		virtual ~NodeComponent() = default;

		inline virtual void UpdateNazaraEntity(Ndk::EntityHandle entity) const override
		{
			Ndk::NodeComponent& nodeComponent = entity->AddComponent<Ndk::NodeComponent>();
			nodeComponent.SetPosition(m_position.first, m_position.second, 0);
			nodeComponent.SetScale(m_scale.first, m_scale.second, 0);
			nodeComponent.Rotate(Nz::EulerAnglesf(0.f, 0.f, m_rotation));
		}

		inline virtual void Save(Ndk::BaseComponent* comp) override
		{
			Ndk::NodeComponent* nodeComp = static_cast<Ndk::NodeComponent*>(comp);
			
			m_position.first = nodeComp->GetPosition().x;
			m_position.second = nodeComp->GetPosition().y;
			m_scale.first = nodeComp->GetScale().x;
			m_scale.second = nodeComp->GetScale().y;
			m_rotation = nodeComp->GetRotation().z;
		}

	protected:
		std::pair<float, float> m_position;
		std::pair<float, float> m_scale;
		float m_rotation;
	};
}
#endif // !NODECOMPONENT_H
