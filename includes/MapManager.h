#pragma once

#include <string>
#include <map>

#include <fstream>
#include <iostream>
#include <filesystem>

#include <Nazara/Utility.hpp>
#include <NDK/Application.hpp>
#include <NDK/Components.hpp>
#include <NDK/Systems.hpp>
#include <NDK/World.hpp>

#include "Map.h"
#include "GraphicsSetManager.h"

const std::string FOLDER_MAP_PATH = "D:/Programmation_2018/NazaraProject/NazaraProject/Ressources/Maps";

namespace fs = std::experimental::filesystem;

class MapManager
{
public:
	MapManager(Ndk::Application & app, GraphicsSetManager& graphicsSetManager) : m_folderMap(FOLDER_MAP_PATH), m_application(app), m_graphicsSetManager(graphicsSetManager) { ; }
	~MapManager() = default;

	bool Exist(const std::string & mapName);
	Map & GetMap(const std::string & mapName) { return m_maps[mapName]; }
	
private:
	bool CreateMap(const std::string & map);

	Ndk::Application & m_application;
	std::string m_folderMap;
	std::map<std::string, Map> m_maps;
	GraphicsSetManager & m_graphicsSetManager;

};