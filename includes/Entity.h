#pragma once

#include <vector>

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include "Component.h"
#include "GraphicsComponent.h"

namespace NzP
{
	//class Component;
	//class GraphicsComponent;

	class Entity
	{
		struct Position;
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			//ar.template register_type<GraphicsComponent>();
			//ar & BOOST_SERIALIZATION_NVP(COMPONENT);
			ar & BOOST_SERIALIZATION_NVP(LAYER_ID);
			ar & BOOST_SERIALIZATION_NVP(COMPONENT);
		}
	public:
		Entity() = default;
		~Entity() = default;

		std::vector<Component*>& GetComponentList() { return COMPONENT; }

		void CreateEntity(std::vector<Ndk::WorldHandle>& wolrdList, std::vector<Ndk::EntityHandle>& entityList)
		{
			entityList.emplace_back(wolrdList[LAYER_ID]->CreateEntity());
			for (auto component : COMPONENT)
			{
				component->UpdateEntity(entityList.back());
			}
		}

	protected:
		unsigned int LAYER_ID;
		
		std::vector<Component*> COMPONENT;
		
	};
}




//BOOST_CLASS_EXPORT_GUID(NzP::Component, "Component")
//BOOST_CLASS_EXPORT_GUID(NzP::GraphicsComponent, "GraphicsComponent")