#pragma once

#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

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

#include <NDK/Application.hpp>
#include <Ndk/Entity.hpp>
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
		bool IsValid() const; // v�rifie que tous les param�tres sont pr�sents et valide pour initialiser le Gset
	};

	class Map;
	using MapConstRef = Nz::ObjectRef<const Map>;
	using MapManager = Nz::ResourceManager<Map, MapParams>;
	using MapRef = Nz::ObjectRef<Map>;

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
			ar & m_filePath;
			std::cout << "Map _ m_filePath : " << m_filePath << std::endl;
			ar & m_size;
			std::cout << "Map _ m_size : " << m_size.first << " : " << m_size.second << std::endl;
			ar & m_nbLayers;
			std::cout << "Mapt _ m_nbLayers : " << m_nbLayers << std::endl;

			std::cout << "Serialize/Deserialize Entity de Map " << std::endl;
			std::cout << "Npmbre d'entites dans la Map : "<< m_entities.size() << std::endl;
			ar & m_entities;
			std::cout << "Npmbre d'entites dans la Map : " << m_entities.size() << std::endl;
			std::cout << "FIN Serialize/Deserialize Map " << std::endl;
		}
		
		//Param�trage du ResourceManager
		///Surcharge de la m�thode LoadFromFile de Nz::Resource
		bool LoadFromFile(const Nz::String& filePath, const MapParams& params = MapManager::GetDefaultParameters());
		///D�clarations du ResourceManager
		static MapManager::ManagerMap s_managerMap;
		static MapManager::ManagerParams s_managerParameters;

		//Variables s�rialisables caract�risant la map
		std::string m_filePath;
		std::pair<float, float> m_size;
		unsigned int m_nbLayers;
		std::vector<Entity> m_entities;

		//Attributs
		std::vector<Ndk::EntityHandle> m_entityList;

		//M�thodes priv�es
		///Serialize et Deserialize permettent la lecture du fichier .map
		///et l'impl�mentation de l'architecture d'une map au format maison (non Nazara)
		bool Deserialize();
		bool Serialize();

	public:
		Map() = default;
		Map(const Nz::String& filePath, const MapParams& params = MapParams());
		~Map() { std::cout << this->GetReferenceCount() << std::endl; }

		//M�thodes publiques
		///M�thode permettant de convertir la Map maison en Map Nazara pouvant �tre rendu
		void DisplayMap(Ndk::WorldHandle& world);
		///Destruction des entit�es de la map aff�ct�es au world (pas tr�s optimis�)
		void HideMap();

		bool IsValid() const;

		template<typename... Args>
		static MapRef New(Args&&... args)
		{
			auto object(std::make_unique<Map>(std::forward<Args>(args)...));
			object->SetPersistent(false);

			return object.release();
		}

		//Accesseurs / Mutateurs
		///Nombre de calques de la map
		const unsigned int GetNbLayers() const { return m_nbLayers; }

		///Taille de la map
		Nz::Vector2f GetSize() const { return Nz::Vector2f{ m_size.first, m_size.second }; }
		void SetSize(Nz::Vector2f size) {
			m_size.first = size.x;
			m_size.second = size.y;
		}
	};
}
#endif // !MAP_H