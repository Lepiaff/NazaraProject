#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <memory>

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/serialization/unique_ptr.hpp>

#include <NDK/Components/CollisionComponent2D.hpp>

#include "Component.h"
#include "GraphicsComponent.h"
#include "NodeComponent.h"
#include "CollidableComponent.h"

namespace NzP
{
	class Entity
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			std::cout << "Serialize/Deserialize Entity" << std::endl;

			ar & m_idLayer;
			std::cout << "CollidableComponent _ m_idLayer : " << m_idLayer << std::endl;

			std::cout << "Serialize/Deserialize des component de Entity " << std::endl;
			ar & m_nodeComponent;
			ar & m_graphicsComponent; 
			ar & m_collidableComponent;

			std::cout << "FIN Serialize/Deserialize de Entity " << std::endl;
		}

		unsigned int m_idLayer;

		boost::shared_ptr<NodeComponent> m_nodeComponent;
		boost::shared_ptr<GraphicsComponent>m_graphicsComponent;
		boost::shared_ptr<CollidableComponent> m_collidableComponent;

	public:
		Entity() = default;
		~Entity() = default;

		const unsigned int GetIdLayer() const { return m_idLayer; }

		inline void UpdateNazaraEntity(Ndk::EntityHandle entity)
		{
			if (m_nodeComponent)
				m_nodeComponent->UpdateNazaraEntity(entity);

			if (m_graphicsComponent)
				m_graphicsComponent->UpdateNazaraEntity(entity);

			if (m_collidableComponent)
				m_collidableComponent->UpdateNazaraEntity(entity);
		}

		inline void Save(const Ndk::EntityHandle& entityHandle)
		{
			if (entityHandle->HasComponent<Ndk::NodeComponent>())
			{
				m_nodeComponent = boost::make_shared<NodeComponent>();
				m_nodeComponent->Save(&entityHandle->GetComponent<Ndk::NodeComponent>());
			}
			if (entityHandle->HasComponent<Ndk::GraphicsComponent>())
			{
				m_graphicsComponent = boost::make_shared<GraphicsComponent>();
				m_graphicsComponent->Save(&entityHandle->GetComponent<Ndk::GraphicsComponent>());
			}
			if (entityHandle->HasComponent<Ndk::CollisionComponent2D>())
			{
				m_collidableComponent = boost::make_shared<CollidableComponent>();
				m_collidableComponent->Save(&entityHandle->GetComponent<Ndk::CollisionComponent2D>());
			}
		}
	};
}
#endif // !ENTITY_H

