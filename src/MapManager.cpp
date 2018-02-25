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

	for (int a = 0; a < 600; a += 32)
	{
		for (int b = 0; b < 800; b += 32)
		{
			fichier2 << "E " << b << " " << a << " GC Village 12 CC 0 0 32 32"<<std::endl;
		}
	}*/

	
	std::ifstream fichier(mapPath.c_str());

	if (fichier)
	{
		std::cout << mapPath << ": Map existante." << std::endl;
		std::string parametre = "";
		Ndk::EntityHandle currentEntity;

		m_maps[mapName] = Map(mapName, m_parrentWorld);

		while (!fichier.eof())
		{
			fichier >> parametre;

			if (parametre == "E") //Entity
			{
				currentEntity = m_maps[mapName].AddEntity();
				std::cout << "Entite cree" << std::endl;

				Ndk::NodeComponent & Nodecomponant = currentEntity->AddComponent<Ndk::NodeComponent>();
				std::cout << "NodeComponant cree" << std::endl;
				float x(0);
				float y(0);
				fichier >> x;
				fichier >> y;
				Nodecomponant.SetPosition(x, y, 0);
			}

			else if(parametre == "GC") //GraphicsComponent
			{
				std::cout << "GraphicsComponant cree" << std::endl;
				Ndk::GraphicsComponent & Graphicscomponant = currentEntity->AddComponent<Ndk::GraphicsComponent>();
				std::string nameGraphicsSet;
				std::size_t idTile;
				fichier >> nameGraphicsSet;
				fichier >> idTile;
				
				if (!m_graphicsSetManager.Load(nameGraphicsSet))
					return false;
				
				Graphicscomponant.Attach(m_graphicsSetManager.GetGraphicsSet(nameGraphicsSet).GetSprite(idTile));
			}

			/*else if (parametre == "CC")//CollisionComponent
			{

			}*/
		}

		//On disable le display
		m_maps[mapName].Hide();
		return true;
	}
	else
	{
		std::cout <<"Map inexistante." << std::endl;
		return false;
	}

}
