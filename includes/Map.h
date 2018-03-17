#pragma once

#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <boost/serialization/version.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/wrapper.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>

#include <Nazara/Core/MovablePtr.hpp>
#include <NDK/Application.hpp>
#include <Ndk/Entity.hpp>
#include <Ndk/World.hpp>
#include <NDK/Components.hpp>
#include <Nazara/Core/HandledObject.hpp>
#include <Nazara/Core/RefCounted.hpp>
#include <Nazara/Core/Resource.hpp>
#include <Nazara/Core/ObjectRef.hpp>
#include <Nazara/Core/ObjectLibrary.hpp>
#include <Nazara/Core/ResourceLoader.hpp>
#include <Nazara/Core/String.hpp>
#include <Nazara/Core/ResourceParameters.hpp>
#include <Nazara/Core/ResourceManager.hpp>

#include "Entity.h"

namespace fs = std::experimental::filesystem;

namespace NzP
{
	struct MapParams : public Nz::ResourceParameters
	{
		friend class Map;
		MapParams() = default;
		Nz::Vector2f size{ 800 , 600 };
		bool IsValid() const; // vérifie que tous les paramètres sont présents et valide pour initialiser le Gset
	};

	class Map;
	using MapConstRef = Nz::ObjectRef<const Map>;
	using MapManager = Nz::ResourceManager<Map, MapParams>;
	using MapRef = Nz::ObjectRef<Map>;
	struct MapImpl {};

	class Map : public Nz::RefCounted, public Nz::Resource
	{
		friend MapManager;
		friend class Utility;

	private:

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			std::cout << "Serialize/Deserialize Map" << std::endl;
			ar & NAME;
			std::cout << "Map _ NAME : " << NAME << std::endl;
			ar & SIZE;
			std::cout << "Map _ SIZE : " << SIZE.first << " : " << SIZE.second << std::endl;
			ar & NB_LAYERS;
			std::cout << "Mapt _ NB_LAYERS : " << NB_LAYERS << std::endl;

			std::cout << "Serialize/Deserialize Entity de Map " << std::endl;
			ar & ENTITIES;
			std::cout << "FIN Serialize/Deserialize Map " << std::endl;
		}

		bool LoadFromFile(const Nz::String& filePath, const MapParams& params = MapManager::GetDefaultParameters());

		Nz::MovablePtr<MapImpl> m_impl = nullptr;
		static MapManager::ManagerMap s_managerMap;
		static MapManager::ManagerParams s_managerParameters;

		//Variables sérialisables
		std::string NAME;
		std::pair<float, float> SIZE;
		unsigned int NB_LAYERS;
		std::vector<Entity> ENTITIES;

		// Autres variables
		std::vector<unsigned int> m_LayerByEntity;
		std::vector<Nz::SpriteRef> m_GSets;
		std::vector<Ndk::EntityHandle> m_entities;

		std::vector<Ndk::WorldHandle> m_layerList;

		bool LoadMap();
		bool SaveMap();

		bool Deserialize();
		bool Serialize();

	public:
		Map() = default;
		Map(const Nz::String& filePath, const MapParams& params = MapParams());
		~Map() = default;

		void SaveMapState();

		bool IsValid() const;

		template<typename... Args>
		static MapRef New(Args&&... args)
		{
			auto object(std::make_unique<Map>(std::forward<Args>(args)...));
			object->SetPersistent(false);

			return object.release();
		}

		Ndk::EntityHandle& AddEntity(const unsigned int layer);
		std::vector<Ndk::WorldHandle>& GetLayers() { return m_layerList; }

		void Display(const bool state);
		void CreateLayers(const unsigned int nbLayers);

		//get et set
		std::vector<Ndk::EntityHandle> GetEntities() const { return m_entities; }

		const std::string& GetName() const { return NAME; }
		void setName(std::string name) { NAME = std::move(name); }

		const unsigned int GetNbLayers() const { return m_layerList.size(); }

		Nz::Vector2f GetSize() const { return Nz::Vector2f{ SIZE.first, SIZE.second }; }
		void SetSize(Nz::Vector2f size) {
			SIZE.first = size.x;
			SIZE.second = size.y;
		}

		void setEntities(std::vector<Ndk::EntityHandle> entities) { m_entities = std::move(entities); }

		const std::vector<std::size_t>& GetLayerByEntity() const { return m_LayerByEntity; }
		void SetLayerByEntity(std::vector<std::size_t> layerByEntity) { m_LayerByEntity = std::move(layerByEntity); }
	};
}
#endif // !MAP_H