#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <memory>

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
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

			ar & BOOST_SERIALIZATION_NVP(LAYER_ID);
			std::cout << "CollidableComponent _ LAYER_ID : " << LAYER_ID << std::endl;

			std::cout << "Serialize/Deserialize NodeComponent de Entity " << std::endl;
			ar & BOOST_SERIALIZATION_NVP(NODE_COMPONENT);
			std::cout << "Serialize/Deserialize GraphicsComponent de Entity " << std::endl;
			ar & BOOST_SERIALIZATION_NVP(GRAPHICS_COMPONENT);
			std::cout << "Serialize/Deserialize CollidableComponent de Entity " << std::endl;
			ar & BOOST_SERIALIZATION_NVP(COLLIDABLE_COMPONENT);

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
			if (NODE_COMPONENT)
			{
				entityList.emplace_back(wolrdList[LAYER_ID]->CreateEntity());
				NODE_COMPONENT->UpdateEntity(entityList.back());
			}

			if (GRAPHICS_COMPONENT)
			{
				entityList.emplace_back(wolrdList[LAYER_ID]->CreateEntity());
				GRAPHICS_COMPONENT->UpdateEntity(entityList.back());
			}

			if (COLLIDABLE_COMPONENT)
			{
				entityList.emplace_back(wolrdList[LAYER_ID]->CreateEntity());
				COLLIDABLE_COMPONENT->UpdateEntity(entityList.back());
			}
		}

		void SaveEntity(const Ndk::EntityHandle& entityHandle)
		{
			if (entityHandle->HasComponent<Ndk::NodeComponent>())
			{
				NODE_COMPONENT = boost::make_shared<NodeComponent>(/*NodeComponent()*/);
				NODE_COMPONENT->Save(&entityHandle->GetComponent<Ndk::NodeComponent>());
			}
			if (entityHandle->HasComponent<Ndk::GraphicsComponent>())
			{
				GRAPHICS_COMPONENT = boost::make_shared<GraphicsComponent>(/*GraphicsComponent()*/);
				GRAPHICS_COMPONENT->Save(&entityHandle->GetComponent<Ndk::GraphicsComponent>());
			}
			if (entityHandle->HasComponent<Ndk::CollisionComponent2D>())
			{
				COLLIDABLE_COMPONENT = boost::make_shared<CollidableComponent>(/*CollidableComponent()*/);
				COLLIDABLE_COMPONENT->Save(&entityHandle->GetComponent<Ndk::CollisionComponent2D>());
			}
		}
	};
}
#endif // !ENTITY_H

