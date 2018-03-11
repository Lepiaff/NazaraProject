#include "MapManager.h"

namespace NzP
{
	bool MapManager::SaveMap(const std::string& mapName)
	{
		if (isLoaded(mapName))
		{
			return SerializeMap(mapName);
		}
		return false;
	}
	bool MapManager::LoadMap(const std::string& mapName)
	{
		if (!isLoaded(mapName))
		{
			return DeserializeMap(mapName);
		}
		return true;
	}

	bool MapManager::isLoaded(const std::string& mapName)
	{
		if (m_maps.find(mapName) == m_maps.end())
		{
			return false;
		}
		return true;
	}

	bool MapManager::SerializeMap(const std::string& mapName)
	{
		fs::path mapPath = m_folderMap + "/" + mapName + "Xml.map";
		std::ofstream fichier(mapPath.c_str());
		boost::archive::xml_oarchive oXMLArchive(fichier);

		NzP::Map& MAP = m_maps[mapName];

		if (fichier)
		{
			oXMLArchive << BOOST_SERIALIZATION_NVP(MAP);
			return true;
		}
		return false;
	}



	bool MapManager::DeserializeMap(const std::string& mapName)
	{
		//temporaire ==>Création du fichier map
		/*fs::path mapPath = m_folderMap + "/" + mapName + "TextFullSize.map";
		std::ofstream fichier(mapPath.c_str());
		fichier << 3 <<std::endl;
		for (int a = 0; a < 600; a += 32)
		{
			for (int b = 0; b < 800; b += 32)
			{
				fichier << "E 0 " << b << " " << a << " G Village 12 C 0 0 32 32"<<std::endl;
			}
		}
		return true;*/

		///Load map.txt
		/*fs::path mapPath = m_folderMap + "/" + mapName + "Text.map";
		std::ifstream fichier(mapPath.c_str());

		if (fichier)
		{
			char parametre;
			Ndk::EntityHandle currentEntity;

			//On a forcement le nombre de layer en premier
			unsigned int i = 0;
			fichier >> i;
			m_maps[mapName] = Map(&m_application, mapName, i);
			
			Nz::Vector2f size;
			float size_;
			fichier >> size_;
			size.x = size_;
			fichier >> size_;
			size.y = size_;
			std::cout << size.x << " " << size.y << std::endl;
			m_maps[mapName].SetSize(size);

			//variables temp
			unsigned int layer{ 0 };
			float x{ 0 };
			float y{ 0 };
			std::string nameGraphicsSet{ "" };
			std::size_t idTile{ 0 };
			Ndk::NodeComponent * nodeComponent = nullptr;
			Ndk::GraphicsComponent * graphicsComponent = nullptr;

			while (!fichier.eof())
			{
				fichier >> parametre;

				switch (parametre)
				{
					case 'E':
						fichier >> layer;
						currentEntity = m_maps[mapName].AddEntity(layer);

						nodeComponent = &currentEntity->AddComponent<Ndk::NodeComponent>();

						fichier >> x;
						fichier >> y;
						nodeComponent->SetPosition(x, y, 0);
						break;

					case 'G':
						graphicsComponent = &currentEntity->AddComponent<Ndk::GraphicsComponent>();
						m_maps[mapName].AddComponentType("SPRITE_COMPONENT");
						m_maps[mapName].AddIdTile(0);
						m_maps[mapName].AddTextureName(mapName);
						fichier >> nameGraphicsSet;
						fichier >> idTile;
						
						Nz::String filePath{ "D:/Programmation_2018/NazaraProject/NazaraProject/Ressources/Tilesets/32x32/Village.png" };
						
						//GraphicsSetParams params;
						//params.sizeTiles = { 32, 32 };

						//GSetManager::Register(filePath, GraphicsSet::New(filePath, params));

						graphicsComponent->Attach(GSetManager::Get(filePath)->GetSprite(idTile));
						break;
				}
			}
			//On cache les entites
			//m_maps[mapName].Display(false);

			//m_maps[mapName].Save();
			//SerializeMap(mapName);
			return true;
		}
		else
		{
			std::cout <<"Map inexistante." << std::endl;
			return false;
		}*/


		///Test serialisation!!!!!!!!!!!!!!!
		fs::path mapPath = m_folderMap + "/" + mapName + "Xml.map";
		std::ifstream fichier(mapPath.c_str());

		if (fichier.is_open())
		{
			boost::archive::xml_iarchive iXMLArchive(fichier);
			m_maps[mapName] = Map(&m_application, mapName);
			Map& MAP = m_maps[mapName];
			iXMLArchive >> BOOST_SERIALIZATION_NVP(MAP);
			MAP.Load();
			return true;
		}
		else { return false; }

	}

}