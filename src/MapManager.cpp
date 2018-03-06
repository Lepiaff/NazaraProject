#include "MapManager.h"

namespace NzP
{
	bool MapManager::LoadMap(const std::string & mapName)
	{
		if (m_maps.find(mapName) == m_maps.end())
		{
			return CreateMap(mapName);
		}

		return true;
	}

	bool MapManager::CreateMap(const std::string & mapName)
	{
		fs::path mapPath = m_folderMap + "/" + mapName + "test.map";
		std::ifstream fichier(mapPath.c_str());
		boost::archive::xml_iarchive iXMLArchive(fichier);

		m_maps[mapName] = NzP::Map(&m_application, mapName);
		NzP::Map& MAP = m_maps[mapName];
				
		if (fichier)
		{
		iXMLArchive >> BOOST_SERIALIZATION_NVP(MAP);
		}



		/*int MONINT = 66;
		int& MA_REF = MONINT;

		std::vector<int> MONINT_VECTOR;
		MONINT_VECTOR.emplace_back(11);
		MONINT_VECTOR.emplace_back(22);
		MONINT_VECTOR.emplace_back(33);
		MONINT_VECTOR.emplace_back(44);
		MONINT_VECTOR.emplace_back(55);
		fs::path mapPath = m_folderMap + "/" + mapName + "test.map";
		std::ofstream fichier(mapPath.c_str());
		boost::archive::xml_oarchive oXMLArchive(fichier);
		oXMLArchive << BOOST_SERIALIZATION_NVP(MA_REF);
		oXMLArchive << BOOST_SERIALIZATION_NVP(MONINT_VECTOR);
		///Test serialization*/

		/*m_maps[mapName] = NzP::Map(&m_application, mapName);
		NzP::Map MAP;
		std::ifstream fichier(mapPath.c_str());
		boost::archive::xml_iarchive iXMLArchive(fichier);
		if (fichier)
		{
			iXMLArchive >> BOOST_SERIALIZATION_NVP(MAP);
		}*/
		///



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


		//std::ifstream fichier(mapPath.c_str());



		/*if (fichier)
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

						if (!m_graphicsSetManager.Load(nameGraphicsSet))
							return false;

						graphicsComponent->Attach(m_graphicsSetManager.GetGraphicsSet(nameGraphicsSet).GetSprite(idTile));
						break;

				}
			}
			//On cache les entites
			//m_maps[mapName].Display(false);


			///Test serialisation!!!!!!!!!!!!!!!
			fs::path mapPath2 = m_folderMap + "/" + mapName + "2.map";

			//temporaire ==>Création du fichier map
			std::ofstream fichier2(mapPath2.c_str());

			boost::archive::xml_oarchive oXMLArchive(fichier2);
			Map& MAP = m_maps[mapName];
			oXMLArchive << BOOST_SERIALIZATION_NVP(MAP);

			///

			return true;
		}
		else
		{
			std::cout <<"Map inexistante." << std::endl;
			return false;
		}*/
		return true;//a supprimer
	}
}