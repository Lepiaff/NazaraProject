#pragma once

#include <string>
#include <vector>

#include <NDK/Application.hpp>

#include <Ndk/Entity.hpp>
#include <Ndk/World.hpp>

class Map
{
public:
	//Map(Ndk::Application & app) : m_application(app);
	Map() = default;
	Map(std::string name, Ndk::WorldHandle & parrent) : m_name(name), m_parrentWorld(parrent) {};
	~Map() = default;

	Ndk::EntityHandle & AddEntity();
	void Display();
	void Hide();

	void SetNbLayers(const unsigned int nbLayers);


private:
	std::string m_name;
	Ndk::WorldHandle m_parrentWorld;
	std::vector<Ndk::EntityHandle> m_entities;
	
	//Ndk::Application & m_application;
	//std::vector<Ndk::WorldHandle> m_layers;

};