#include "Map.h"


Ndk::EntityHandle & Map::AddEntity()
{
	m_entities.emplace_back(m_parrentWorld->CreateEntity());
	return m_entities.back();
}

void Map::Display()
{
	for (auto i : m_entities)
	{
		i->Enable();
	}
}

void Map::Hide()
{
	for (auto i : m_entities)
	{
		i->Disable();
	}
}

void Map::SetNbLayers(const unsigned int nbLayers)
{
	//for (auto i = 0; i < nbLayers; i++){}
		//m_layers.emplace_back();
}
