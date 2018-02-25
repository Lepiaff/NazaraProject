#pragma once

#include <string>
#include <map>

#include <Nazara/Graphics.hpp>

#include "GraphicsSet.h"

const std::string GRAPHICS_SET_FOLDER_PATH = "D:/Programmation_2018/NazaraProject/NazaraProject/Ressources/Tilesets/32x32";

class GraphicsSetManager
{
public:
	GraphicsSetManager() = default;
	~GraphicsSetManager() = default;

	//M�thodes libres
	bool Load(std::string & name);
	GraphicsSet & GetGraphicsSet(std::string & name) { return m_GraphicsSetMap[name]; }


private:

	//M�thodes internes
	bool Exist(const std::string & name);
	

	//Atributs
	std::map<std::string, GraphicsSet> m_GraphicsSetMap;
};