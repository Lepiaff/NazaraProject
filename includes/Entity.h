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
			ar & BOOST_SERIALIZATION_NVP(LAYER_ID);
			ar & BOOST_SERIALIZATION_NVP(COMPONENT);
		}
		/*friend class boost::serialization::access;
		template<class Archive>
		void save(Archive& ar, const unsigned int version) const
		{
			ar & BOOST_SERIALIZATION_NVP(LAYER_ID);
			std::size_t NB_COMPONENT = COMPONENT.size();
			ar & BOOST_SERIALIZATION_NVP(NB_COMPONENT);
			ar & BOOST_SERIALIZATION_NVP(COMPONENT);
		}

		template<class Archive>
		void load(Archive& ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(LAYER_ID);
			std::size_t NB_COMPONENT = 0;
			ar & BOOST_SERIALIZATION_NVP(NB_COMPONENT);
			COMPONENT.clear();
			COMPONENT.reserve(NB_COMPONENT);
			while (NB_COMPONENT-- >= 0)
			{
				GraphicsComponent* gComp;
				ar & boost::serialization::make_nvp("GRAPHICSCOMPONENT", gComp);
				if (gComp) { COMPONENT.emplace_back(boost::make_shared<GraphicsComponent>(*gComp)); }

				NodeComponent* nComp;
				ar & boost::serialization::make_nvp("NODECOMPONENT", nComp);
				if (nComp) { COMPONENT.emplace_back(boost::make_shared<NodeComponent>(*nComp)); }
			}
		}
		BOOST_SERIALIZATION_SPLIT_MEMBER()*/

		unsigned int LAYER_ID;
		std::vector<boost::shared_ptr<Component>> COMPONENT;

	public:
		Entity() = default;
		~Entity() = default;

		//std::vector<std::unique_ptr<Component>>& GetComponentList() { return COMPONENT; }

		void CreateEntity(std::vector<Ndk::WorldHandle>& wolrdList, std::vector<Ndk::EntityHandle>& entityList)
		{
			entityList.emplace_back(wolrdList[LAYER_ID]->CreateEntity());
			for (std::size_t i = 0 ; i < COMPONENT.size() ; ++i)
			{
				COMPONENT[i]->UpdateEntity(entityList.back());
			}
		}

		void SaveEntity(const Ndk::EntityHandle& entityHandle)
		{
			if (entityHandle->HasComponent<Ndk::NodeComponent>())
			{
				//COMPONENT.emplace_back(boost::make_shared<NodeComponent>());
				std::unique_ptr<Component> comp = std::make_unique<NodeComponent>();
				COMPONENT.emplace_back(std::move(comp));
				COMPONENT.back()->Save(&entityHandle->GetComponent<Ndk::NodeComponent>());
			}
			if (entityHandle->HasComponent<Ndk::GraphicsComponent>())
			{
				//COMPONENT.emplace_back(boost::make_shared<GraphicsComponent>());
				std::unique_ptr<Component> comp = std::make_unique<GraphicsComponent>();
				COMPONENT.emplace_back(std::move(comp));
				COMPONENT.back()->Save(&entityHandle->GetComponent<Ndk::GraphicsComponent>());
			}
			if (entityHandle->HasComponent<Ndk::CollisionComponent2D>())
			{
				//COMPONENT.emplace_back(boost::make_shared<CollidableComponent>());
				std::unique_ptr<Component> comp = std::make_unique<CollidableComponent>();
				COMPONENT.emplace_back(std::move(comp));
				COMPONENT.back()->Save(&entityHandle->GetComponent<Ndk::CollisionComponent2D>());
			}
		}
	};
}
#endif // !ENTITY_H

