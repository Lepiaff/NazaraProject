#pragma once

#ifndef MAP_H
#define MAP_H


#include <string>
#include <vector>

#include <boost/serialization/version.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/wrapper.hpp>
#include <boost/serialization/utility.hpp>

#include <NDK/Application.hpp>
#include <Ndk/Entity.hpp>
#include <Ndk/World.hpp>
#include <NDK/Components.hpp>

#include "Entity.h"

namespace NzP
{
	class Map
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			std::cout << "Serialize/Deserialize Map" << std::endl;
			ar & BOOST_SERIALIZATION_NVP(NAME);
			std::cout << "Map _ NAME : " << NAME << std::endl;
			ar & BOOST_SERIALIZATION_NVP(SIZE);
			std::cout << "Map _ SIZE : " << SIZE.first <<" : " << SIZE.second << std::endl;
			ar & BOOST_SERIALIZATION_NVP(NB_LAYERS);
			std::cout << "Mapt _ NB_LAYERS : " << NB_LAYERS << std::endl;

			std::cout << "Serialize/Deserialize Entity de Map " << std::endl;
			ar & BOOST_SERIALIZATION_NVP(ENTITIES);
			std::cout << "FIN Serialize/Deserialize Map " << std::endl;
		}

	public:
		Map() = default;
		Map(Ndk::Application* app, std::string name, const unsigned int nbLayer = 1);
		Map(Ndk::Application* app);
		~Map() = default;

		bool Load();
		bool Save();


		Ndk::EntityHandle & AddEntity(const unsigned int layer);
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

		const std::vector<std::string>& GetComponentsType() const { return m_componentsType; }
		void SetComponentsType(std::vector<std::string> componentsType) { m_componentsType = std::move(componentsType); }
		void AddComponentType(std::string nameComponentType) { m_componentsType.emplace_back(std::move(nameComponentType)); }

		const std::vector<unsigned int>& GetIdTiles() const { return m_idTiles; }
		void SetIdTiles(std::vector<unsigned int> idtiles) { m_idTiles = std::move(idtiles); }
		void AddIdTile(unsigned int idTile) { m_idTiles.emplace_back(std::move(idTile)); }

		const std::vector<std::string>& GetTextureNames() const { return m_textureNames; }
		void SetTextureNames(std::vector<std::string> textureNames) { m_textureNames = std::move(textureNames); }
		void AddTextureName(std::string textureName) { m_textureNames.emplace_back(std::move(textureName)); }

	protected:

		//Variables sérialisables
		std::string NAME;
		std::pair<float, float> SIZE;
		unsigned int NB_LAYERS;
		std::vector<Entity> ENTITIES;


		// Autres variables
		std::vector<unsigned int> m_LayerByEntity;
		std::vector<Ndk::EntityHandle> m_entities;

		Ndk::Application* m_application;
		std::vector<Ndk::WorldHandle> m_layerList;

		std::vector<std::string> m_componentsType;
		std::vector<unsigned int> m_idTiles;
		std::vector<std::string> m_textureNames;

	};
}
#endif // !MAP_H