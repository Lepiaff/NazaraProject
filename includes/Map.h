#pragma once

#include <string>
#include <vector>

#include <boost/serialization/version.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/collection_size_type.hpp>


#include <NDK/Application.hpp>
#include <Ndk/Entity.hpp>
#include <Ndk/World.hpp>
#include <NDK/Components.hpp>

#include "Entity.h"

namespace NzP
{
	class Map
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(NAME);
			ar & BOOST_SERIALIZATION_NVP(SIZE_X);
			ar & BOOST_SERIALIZATION_NVP(SIZE_Y);
			ar & BOOST_SERIALIZATION_NVP(NB_LAYERS);
			ar & BOOST_SERIALIZATION_NVP(ENTITIES);
		}

	public:
		Map() = default;
		Map(Ndk::Application* app, std::string name, const unsigned int nbLayer = 0);
		~Map() = default;

		bool Load();

		Ndk::EntityHandle & AddEntity(const unsigned int layer);
		std::vector<Ndk::WorldHandle>& GetLayers() { return m_layerList; } ///Pourquoi je ne peux pas rendre cette méthode const ??
		void Display(const bool state);


		//get et set
		std::vector<Ndk::EntityHandle> GetEntities() const { return m_entities; }

		//const std::string& GetName() const { return m_name; }
		//void setName(std::string name) { m_name = std::move(name); }

		const unsigned int GetNbLayers() const { return m_layerList.size(); }
		void CreateLayers(const unsigned int nbLayers);

		//const Nz::Vector2f& GetSize() const { return m_size; }
		//void SetSize(Nz::Vector2f size) { m_size = std::move(size); }

		void setEntities(std::vector<Ndk::EntityHandle> entities) { m_entities = std::move(entities); }

		const std::vector<std::size_t>& GetLayerByEntity() const { return m_LayerByEntity; }
		void SetLayerByEntity(std::vector<std::size_t> layerByEntity) { m_LayerByEntity = std::move(layerByEntity); }

		const std::vector<std::string>& GetComponentsType() const { return m_componentsType; }
		void SetComponentsType(std::vector<std::string> componentsType) { m_componentsType = std::move(componentsType); }
		void AddComponentType(std::string nameComponentType) { m_componentsType.emplace_back(std::move(nameComponentType)); }

		const std::vector<unsigned int>& GetIdTiles() const { return m_idTiles; }
		void SetIdTiles(std::vector<unsigned int> idtiles) { m_idTiles = std::move(idtiles); }
		void AddIdTile(unsigned int idTile) { m_idTiles.emplace_back(std::move(idTile)); }

		const std::vector<std::string>& GetTextureNames() const { return m_textureNames; }
		void SetTextureNames(std::vector<std::string> textureNames) { m_textureNames = std::move(textureNames); }
		void AddTextureName(std::string textureName) { m_textureNames.emplace_back(std::move(textureName)); }

	protected:

		//Variables sérialisables
		std::string NAME;
		float SIZE_X;
		float SIZE_Y;
		unsigned int NB_LAYERS;
		std::vector<NzP::Entity> ENTITIES;


		// Autres variables
		std::vector<unsigned int> m_LayerByEntity;
		std::vector<Ndk::EntityHandle> m_entities;

		Ndk::Application* m_application;
		std::vector<Ndk::WorldHandle> m_layerList;

		std::vector<std::string> m_componentsType;
		std::vector<unsigned int> m_idTiles;
		std::vector<std::string> m_textureNames;

	};
}


//BOOST_CLASS_VERSION(Map, 1)
/*namespace boost
{
	namespace serialization
	{
		template<class Archive>
		void save(Archive & archive, const Map & map, const unsigned int version)
		{
			//Enregistrement des caractèristiques de la map
			std::string NAME = map.GetName();
			archive & BOOST_SERIALIZATION_NVP(NAME);
			Nz::Vector2f SIZE_MAP = map.GetSize();
			archive & BOOST_SERIALIZATION_NVP(SIZE_MAP.x);
			archive & BOOST_SERIALIZATION_NVP(SIZE_MAP.y);
			unsigned int NB_LAYER = map.GetNbLayers();
			archive & BOOST_SERIALIZATION_NVP(NB_LAYER);
		
			std::vector<Ndk::EntityHandle> ENTITIES = map.GetEntities() ;

			int idSprite = 0;
			int idComponant = 0;

			for (auto entity : ENTITIES)
			{
				//NODE COMPONENT OBLIGATOIRE
				Ndk::NodeComponent& NODE_COMPONENT = entity->GetComponent<Ndk::NodeComponent>();
				
				///Position
				Nz::Vector3f POSITION = NODE_COMPONENT.GetPosition();
				archive & BOOST_SERIALIZATION_NVP(POSITION.x);
				archive & BOOST_SERIALIZATION_NVP(POSITION.y);
				///Scale
				Nz::Vector3f SCALE = NODE_COMPONENT.GetScale();
				archive & BOOST_SERIALIZATION_NVP(SCALE.x);
				archive & BOOST_SERIALIZATION_NVP(SCALE.y);
				///ROTATION
				float ROTATION_x = NODE_COMPONENT.GetRotation().x;
				float ROTATION_y = NODE_COMPONENT.GetRotation().y;

				archive & BOOST_SERIALIZATION_NVP(ROTATION_x);
				archive & BOOST_SERIALIZATION_NVP(ROTATION_y);
				

				//COMPONENT TYPE
				const std::vector<std::string>& componentType = map.GetComponentsType();
				std::string COMPONANT_TYPE;

				
					COMPONANT_TYPE = componentType[i];
					archive & BOOST_SERIALIZATION_NVP(COMPONANT_TYPE);
					if (COMPONANT_TYPE == "SPRITE_COMPONENT")
					{
						std::string TEXTURE_NAME = map.GetTextureNames()[idSprite];
						archive & BOOST_SERIALIZATION_NVP(TEXTURE_NAME);

						unsigned int ID_TILE = map.GetIdTiles()[idSprite];
						archive & BOOST_SERIALIZATION_NVP(ID_TILE);

						/*float POSITION_X = entity->GetComponent<Ndk::GraphicsComponent>().GetBoundingVolume().aabb.x;
						float POSITION_Y = entity->GetComponent<Ndk::GraphicsComponent>().GetBoundingVolume().aabb.y;
						float LARGEUR = entity->GetComponent<Ndk::GraphicsComponent>().GetBoundingVolume().aabb.width;
						float HAUTEUR = entity->GetComponent<Ndk::GraphicsComponent>().GetBoundingVolume().aabb.height;
						archive & BOOST_SERIALIZATION_NVP(POSITION_X);
						archive & BOOST_SERIALIZATION_NVP(POSITION_Y);
						archive & BOOST_SERIALIZATION_NVP(LARGEUR);
						archive & BOOST_SERIALIZATION_NVP(HAUTEUR);
						idComponant++;
						idSprite++;

					}
					else if(COMPONANT_TYPE == "TEXT_SPRITE_COMPONENT")
					{

					}
					else if(COMPONANT_TYPE == "COLLISION_COMPONENT_2D")
					{

					}
					else if(COMPONANT_TYPE == "CONTROL_COMPONENT")
					{

					}
					else if (COMPONANT_TYPE == "EVENT_COMPONENT")
					{

					}
			}
		}

		template<class Archive>
		void load(Archive & archive, const Map & map, const unsigned int version)
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
		}
	} // namespace serialization
} // namespace boost
BOOST_SERIALIZATION_SPLIT_MEMBER(Map)
BOOST_SERIALIZATION_SPLIT_FREE(Map)
*/