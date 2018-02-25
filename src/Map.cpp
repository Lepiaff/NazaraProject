#include "Map.h"


Map::Map(Ndk::Application * app, std::string name, const unsigned int nbLayer) : m_application(app), m_name(name)
{
	SetNbLayers(nbLayer);
}

Ndk::EntityHandle & Map::AddEntity(const unsigned int layer)
{
	m_entities.emplace_back(m_layersList[layer]->CreateEntity());
	return m_entities.back();
}

void Map::Display(const bool state)
{
	for (auto entity : m_entities)
	{
		if (state)
		{
			entity->Enable();
		}
		else
		{
			entity->Disable();
		}
	}
}

void Map::SetNbLayers(const int nbLayers)
{
	for (auto i = 0; i < nbLayers; i++){}
		m_layersList.emplace_back(&m_application->AddWorld());
}
