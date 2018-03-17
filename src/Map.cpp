#include "Map.h"

namespace NzP
{
	
	Map::Map(const Nz::String& filePath, const MapParams& params) : NAME(filePath.ToStdString())
	{
		SetFilePath(filePath);
		//m_application = Ndk::Application::Instance();
		SIZE.first = 0;
		SIZE.second = 0;
		NB_LAYERS = 0;
		ENTITIES.clear();
	}

	bool Map::LoadFromFile(const Nz::String & filePath, const MapParams & params)
	{
		SetFilePath(filePath);
		std::cout << "Map / LoadFromFile : " << filePath << std::endl;
		if (params.IsValid())
			s_managerParameters = params;
		if (!Deserialize())
		{
			std::cout << "Map / LoadFromFile : Echec" << std::endl;
			return false;
		}
		std::cout << "Map / LoadFromFile : Done" << std::endl;
		MapManager::Register(filePath, this);
		std::cout << "Map registered" << std::endl;
		return true;
	}
	bool Map::Deserialize()
	{
		fs::path mapPath = GetFilePath().ToStdString();
		std::ifstream fichier(mapPath.c_str());

		if (fichier.is_open())
		{
			boost::archive::binary_iarchive iBinArchive(fichier);
			Map& MAP = *this;
			iBinArchive >> MAP;
			MAP.LoadMap();
			return true;
		}
		else { return false; }
	}

	bool Map::Serialize()
	{
		fs::path mapPath = GetFilePath().ToStdString();
		std::ofstream fichier(mapPath.c_str());
		if (fichier.is_open())
		{
			boost::archive::binary_oarchive oBinArchive(fichier);
			NzP::Map& MAP = *this;
			oBinArchive << MAP;
			return true;
		}
		return false;
	}

	bool Map::LoadMap()
	{
		CreateLayers(NB_LAYERS);//J'instancie autant de world qu'il y a de layer à ma map

		for (auto entity : ENTITIES)//Je créé les entités
		{
			entity.CreateEntity(m_layerList, m_entities);
		}
		return true;
	}

	bool Map::SaveMap()
	{
		ENTITIES.clear();
		for (auto entity : m_entities)
		{
			ENTITIES.emplace_back(Entity());
			ENTITIES.back().SaveEntity(entity);
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
		NB_LAYERS = nbLayers;
		for (unsigned int i = 0; i < NB_LAYERS; i++)
		{
			m_layerList.emplace_back(&Ndk::Application::Instance()->AddWorld());
		}
	}

	bool MapParams::IsValid() const
	{
		if(size.x > 0 && size.y > 0)
			return true;

		return false;
	}

	void Map::SaveMapState()
	{
		SaveMap();
		Serialize();
	}

	bool Map::IsValid() const
	{
		return true;
		//return m_impl != nullptr;
	}

	MapManager::ManagerMap Map::s_managerMap;
	MapManager::ManagerParams Map::s_managerParameters;
}
