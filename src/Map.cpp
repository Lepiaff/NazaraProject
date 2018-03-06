#include "Map.h"

namespace NzP
{
	Map::Map(Ndk::Application * app, std::string name, const unsigned int nbLayer) : m_application(app), NAME(name)
	{
		CreateLayers(nbLayer);
	}









	bool Map::Load()
	{
		//J'instancie autant de world qu'il y a de layer à ma map
		CreateLayers(NB_LAYERS);
		/*for (auto i = 0; i < NB_LAYERS; ++i)
			m_layerList.emplace_back(m_application->AddWorld());*/

		//Je créé les entités
		for (auto entity : ENTITIES)
		{
			entity.CreateEntity(m_layerList, m_entities);
		}
		return true;
	}








	Ndk::EntityHandle & Map::AddEntity(const unsigned int layer)
	{
		m_entities.emplace_back(m_layerList[layer]->CreateEntity());
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

	void Map::CreateLayers(const unsigned int nbLayers)
	{
		for (unsigned int i = 0; i < nbLayers; i++) {}
			m_layerList.emplace_back(&m_application->AddWorld());
	}
}