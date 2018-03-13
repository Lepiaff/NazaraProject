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

			ar & LAYER_ID;
			std::cout << "CollidableComponent _ LAYER_ID : " << LAYER_ID << std::endl;

			std::cout << "Serialize/Deserialize NodeComponent de Entity " << std::endl;
			ar & NODE_COMPONENT;
			std::cout << "Serialize/Deserialize GraphicsComponent de Entity " << std::endl;
			ar & GRAPHICS_COMPONENT; 
			std::cout << "Serialize/Deserialize CollidableComponent de Entity " << std::endl;
			ar & COLLIDABLE_COMPONENT;

			std::cout << "FIN Serialize/Deserialize Entity de Map " << std::endl;
		}

		unsigned int LAYER_ID;

		boost::shared_ptr<NodeComponent> NODE_COMPONENT;
		boost::shared_ptr<GraphicsComponent>GRAPHICS_COMPONENT;
		boost::shared_ptr<CollidableComponent> COLLIDABLE_COMPONENT;

	public:
		Entity() = default;
		~Entity() = default;

		void CreateEntity(std::vector<Ndk::WorldHandle>& wolrdList, std::vector<Ndk::EntityHandle>& entityList)
		{
			entityList.emplace_back(wolrdList[LAYER_ID]->CreateEntity());
			if (NODE_COMPONENT)
				NODE_COMPONENT->UpdateEntity(entityList.back());

			if (GRAPHICS_COMPONENT)
				GRAPHICS_COMPONENT->UpdateEntity(entityList.back());

			if (COLLIDABLE_COMPONENT)
				COLLIDABLE_COMPONENT->UpdateEntity(entityList.back());
		}

		void SaveEntity(const Ndk::EntityHandle& entityHandle)
		{
			if (entityHandle->HasComponent<Ndk::NodeComponent>())
			{
				NODE_COMPONENT = boost::make_shared<NodeComponent>();
				NODE_COMPONENT->Save(&entityHandle->GetComponent<Ndk::NodeComponent>());
			}
			if (entityHandle->HasComponent<Ndk::GraphicsComponent>())
			{
				GRAPHICS_COMPONENT = boost::make_shared<GraphicsComponent>();
				GRAPHICS_COMPONENT->Save(&entityHandle->GetComponent<Ndk::GraphicsComponent>());
			}
			if (entityHandle->HasComponent<Ndk::CollisionComponent2D>())
			{
				COLLIDABLE_COMPONENT = boost::make_shared<CollidableComponent>();
				COLLIDABLE_COMPONENT->Save(&entityHandle->GetComponent<Ndk::CollisionComponent2D>());
			}
		}
	};
}
#endif // !ENTITY_H

