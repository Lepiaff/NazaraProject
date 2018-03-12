#include "GraphicsSet.h"

namespace NzP
{
	GraphicsSet::GraphicsSet(const Nz::String& filePath, const GraphicsSetParams& params) : Nz::RefCounted(), Nz::Resource()
	{
		SetFilePath(filePath);
		s_managerParameters = params;
		LoadMaterial();
	}

	unsigned int GraphicsSet::GetSpriteId(Nz::Rectf textureRect)
	{
		//A implémenter
		return 0;
	}

	Nz::SpriteRef GraphicsSet::GetSprite(std::size_t idSprite)
	{
		return (idSprite < spriteList.size() ? spriteList[idSprite] : Nz::SpriteRef());
	}

	bool GraphicsSet::LoadMaterial()
	{
		if (!s_managerParameters.IsValid())
			return false;

		material = Nz::Material::New();
		if (material->LoadFromFile(GetFilePath()))
		{
			material->EnableBlending(true);
			material->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
			material->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
			material->EnableDepthWrite(false);

			CreateSpriteList();

			return true;
		}
		return false;
	}

	void GraphicsSet::CreateSpriteList()
	{
		Nz::SpriteRef tempSprite = Nz::Sprite::New(material);
		std::size_t nbTileHeight = static_cast<std::size_t>(tempSprite->GetSize().y / s_managerParameters.sizeTiles.y);
		std::size_t nbTileWidth = static_cast<std::size_t>(tempSprite->GetSize().x / s_managerParameters.sizeTiles.x);

		spriteList.clear(); //on initialiser la list pour être certain qu'elle est vide avant de la remplir
		for (std::size_t j = 0; j < nbTileHeight; j++)
		{
			for (std::size_t i = 0; i < nbTileWidth; i++)
			{
				Nz::Rectui textureBox(i*s_managerParameters.sizeTiles.x, j*s_managerParameters.sizeTiles.y, s_managerParameters.sizeTiles.x, s_managerParameters.sizeTiles.y);
				spriteList.emplace_back(Nz::Sprite::New(material));
				spriteList.back()->SetTextureRect(textureBox);
				spriteList.back()->SetSize(static_cast<Nz::Vector2f>(s_managerParameters.sizeTiles));
			}
		}
	}

	bool GraphicsSetParams::IsValid() const
	{
		if (sizeTiles.x == 0 || sizeTiles.y == 0)
		{
			std::cout << "GraphicsParam invalide ! (Penser à initialiser la taille des tuiles)" << std::endl;
			return false;
		}
		return true;
	}

	bool GraphicsSet::IsValid() const
	{
		return true;
		//return m_impl != nullptr;
	}

	bool GraphicsSet::Initialize()
	{
		/*if (!GSetLibrary::Initialize())
		{
			NazaraError("Failed to initialise library");
			return false;
		}*/

		if (!GSetManager::Initialize())
		{
			NazaraError("Failed to initialise manager");
			return false;
		}

		return true;
	}

	void GraphicsSet::Uninitialize()
	{
		GSetManager::Uninitialize();
		//GSetLibrary::Uninitialize();
	}

	//Méthode de chargement de la ressource
	//Dans ce cas-ci, appelle la méthode LoadMaterial pour charger la texture
	bool GraphicsSet::LoadFromFile(const Nz::String& filePath, const GraphicsSetParams& params)
	{
		SetFilePath(filePath);
		std::cout << "GraphicsSet / LoadFromFile : " << filePath << std::endl;
		if (params.IsValid())
			s_managerParameters = params;
		if (!LoadMaterial())
		{
			std::cout << "GraphicsSet / LoadFromFile : Echec" << std::endl;
			return false;
		}
		std::cout << "GraphicsSet / LoadFromFile : Done" << std::endl;
		GSetManager::Register(filePath, this);
		std::cout << "GraphicsSet registered" << std::endl;
		return true;
	}




	GSetLibrary::LibraryMap GraphicsSet::s_library;
	GSetLoader::LoaderList GraphicsSet::s_loaders;
	GSetManager::ManagerMap GraphicsSet::s_managerMap;
	GSetManager::ManagerParams GraphicsSet::s_managerParameters;
}

