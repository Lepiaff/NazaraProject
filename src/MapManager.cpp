#include "MapManager.h"

bool MapManager::Exist(const std::string & mapName)
{
	if (m_maps.find(mapName) == m_maps.end())
	{
		return CreateMap(mapName);
	}

	return true;
}

bool MapManager::CreateMap(const std::string & mapName)
{
	fs::path mapPath = m_folderMap + "/" + mapName + ".map";

	//temporaire ==>Création du fichier map
	/*std::ofstream fichier2(mapPath.c_str());

	fichier2 << 3 <<std::endl;
	for (int a = 0; a < 600; a += 32)
	{
		for (int b = 0; b < 800; b += 32)
		{
			fichier2 << "E 0 " << b << " " << a << " G Village 12 C 0 0 32 32"<<std::endl;
		}
	}*/

	
	std::ifstream fichier(mapPath.c_str());

	if (fichier)
	{
		std::cout << mapPath << ": Map existante." << std::endl;
		char parametre;
		Ndk::EntityHandle currentEntity;

		//On a forcement le nombre de layer en premier
		unsigned int i = 0;
		fichier >> i;
		m_maps[mapName] = Map(&m_application, mapName, i);

		//variables temp
		unsigned int layer{ 0 };
		float x{ 0 };
		float y{ 0 };
		std::string nameGraphicsSet{ "" };
		std::size_t idTile{ 0 };
		Ndk::NodeComponent * Nodecomponant = nullptr;
		Ndk::GraphicsComponent * Graphicscomponant = nullptr;

		while (!fichier.eof())
		{
			fichier >> parametre;

			switch (parametre)
			{
				case 'E':
					fichier >> layer;
					currentEntity = m_maps[mapName].AddEntity(layer);

					Nodecomponant = &currentEntity->AddComponent<Ndk::NodeComponent>();

					fichier >> x;
					fichier >> y;
					Nodecomponant->SetPosition(x, y, 0);
					break;

				case 'G':
					Graphicscomponant = &currentEntity->AddComponent<Ndk::GraphicsComponent>();
					fichier >> nameGraphicsSet;
					fichier >> idTile;

					if (!m_graphicsSetManager.Load(nameGraphicsSet))
						return false;

					Graphicscomponant->Attach(m_graphicsSetManager.GetGraphicsSet(nameGraphicsSet).GetSprite(idTile));
					break;

			}
		}

		//On cache les entites
		//m_maps[mapName].Display(false);
		return true;
	}
	else
	{
		std::cout <<"Map inexistante." << std::endl;
		return false;
	}

}
