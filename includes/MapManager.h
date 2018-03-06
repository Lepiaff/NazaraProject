#pragma once

#include <string>
#include <map>

#include <fstream>
#include <iostream>
#include <filesystem>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/scoped_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include <Nazara/Utility.hpp>
#include <NDK/Application.hpp>
#include <NDK/Components.hpp>
#include <NDK/Systems.hpp>
#include <NDK/World.hpp>

#include "Map.h"
#include "GraphicsSetManager.h"

const std::string FOLDER_MAP_PATH = "D:/Programmation_2018/NazaraProject/NazaraProject/Ressources/Maps";

namespace fs = std::experimental::filesystem;

namespace NzP
{
	class MapManager
	{
	public:
		MapManager(Ndk::Application & app, NzP::GraphicsSetManager& graphicsSetManager) :
			m_folderMap(FOLDER_MAP_PATH),
			m_application(app),
			m_graphicsSetManager(graphicsSetManager) {}

		~MapManager() = default;

		bool LoadMap(const std::string& mapName);
		NzP::Map& GetMap(const std::string& mapName) { return m_maps[mapName]; }

	private:
		bool CreateMap(const std::string& map);

		Ndk::Application & m_application;
		std::string m_folderMap;
		std::map<std::string, NzP::Map> m_maps;
		NzP::GraphicsSetManager & m_graphicsSetManager;

	};
}