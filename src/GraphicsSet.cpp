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
		return (idSprite < s_managerParameters.spriteList.size() ? s_managerParameters.spriteList[idSprite] : Nz::SpriteRef());
	}

	bool GraphicsSet::LoadMaterial()
	{
		if (!s_managerParameters.IsValid())
			return false;

		s_managerParameters.material = Nz::Material::New();
		if (s_managerParameters.material->LoadFromFile(GetFilePath()))
		{
			s_managerParameters.material->EnableBlending(true);
			s_managerParameters.material->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
			s_managerParameters.material->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
			s_managerParameters.material->EnableDepthWrite(false);

			CreateSpriteList();

			return true;
		}
		return false;
	}

	void GraphicsSet::CreateSpriteList()
	{
		Nz::SpriteRef tempSprite = Nz::Sprite::New(s_managerParameters.material);
		std::size_t nbTileHeight = static_cast<std::size_t>(tempSprite->GetSize().y / s_managerParameters.sizeTiles.y);
		std::size_t nbTileWidth = static_cast<std::size_t>(tempSprite->GetSize().x / s_managerParameters.sizeTiles.x);

		s_managerParameters.spriteList.clear(); //on initialiser la list pour être certain qu'elle est vide avant de la remplir
		for (std::size_t j = 0; j < nbTileHeight; j++)
		{
			for (std::size_t i = 0; i < nbTileWidth; i++)
			{
				Nz::Rectui textureBox(i*s_managerParameters.sizeTiles.x, j*s_managerParameters.sizeTiles.y, s_managerParameters.sizeTiles.x, s_managerParameters.sizeTiles.y);
				s_managerParameters.spriteList.emplace_back(Nz::Sprite::New(s_managerParameters.material));
				s_managerParameters.spriteList.back()->SetTextureRect(textureBox);
				s_managerParameters.spriteList.back()->SetSize(static_cast<Nz::Vector2f>(s_managerParameters.sizeTiles));
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

	//GSetLibrary::LibraryMap GraphicsSet::s_library;
	//GSetLoader::LoaderList GraphicsSet::s_loaders;
	GSetManager::ManagerMap GraphicsSet::s_managerMap;
	GSetManager::ManagerParams GraphicsSet::s_managerParameters;
}