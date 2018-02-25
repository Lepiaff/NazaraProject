#pragma once

#include <string>
#include <vector>

#include <NDK/Application.hpp>

#include <Ndk/Entity.hpp>
#include <Ndk/World.hpp>

class Map
{
public:
	Map() = default;
	Map(Ndk::Application * app, std::string name, const unsigned int nbLayer);
	~Map() = default;

	Ndk::EntityHandle & AddEntity(const unsigned int layer);
	std::vector<Ndk::WorldHandle> & GetLayers() { return m_layersList; }
	void Display(const bool state);

private:
	void SetNbLayers(const int nbLayers);

	std::string m_name;
	std::vector<Ndk::EntityHandle> m_entities;
	
	Ndk::Application * m_application;
	std::vector<Ndk::WorldHandle> m_layersList;
	
};