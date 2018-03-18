#include "Map.h"

namespace NzP
{
	
	Map::Map(const Nz::String& filePath, const MapParams& params) : m_filePath(filePath.ToStdString())
	{
		SetFilePath(filePath);
		m_size.first = 0;
		m_size.second = 0;
		m_nbLayers = 0;
		m_entities.clear();
	}

	bool Map::Deserialize()
	{
		fs::path mapPath = GetFilePath().ToStdString();
		std::ifstream fichier(mapPath.c_str());

		if (fichier.is_open())
		{
			boost::archive::binary_iarchive iBinArchive(fichier);
			iBinArchive >> *this;
			return true;
		}
		else { return false; }
	}

	void Map::DisplayMap(Ndk::WorldHandle& world)
	{
		if(!m_entityList.empty())
			m_entityList.clear();
		///Réorganise les entités par idLayer dans le vector pour que l'ordre d'affichage soit correcte
		std::sort(m_entities.begin(), m_entities.end(),	[](const Entity& e1, const Entity& e2) {
			return e1.GetIdLayer() < e2.GetIdLayer(); });

		for (auto entity : m_entities)
		{
			m_entityList.emplace_back(world->CreateEntity());
				entity.UpdateNazaraEntity(m_entityList.back());
		}
	}

	void Map::HideMap()
	{
		for (auto entity : m_entityList)
			entity->Kill();
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
		return true;
	}

	bool Map::IsValid() const
	{
		return true;
	}

	///Méthode pour le ResourceManager
	bool MapParams::IsValid() const
	{
		if (size.x > 0 && size.y > 0)
			return true;
		return false;
	}

	bool Map::Serialize()
	{
		fs::path mapPath = GetFilePath().ToStdString();
		std::ofstream fichier(mapPath.c_str());
		if (fichier.is_open())
		{
			boost::archive::binary_oarchive oBinArchive(fichier);
			oBinArchive << *this;
			return true;
		}
		return false;
	}

	MapManager::ManagerMap Map::s_managerMap;
	MapManager::ManagerParams Map::s_managerParameters;
}
