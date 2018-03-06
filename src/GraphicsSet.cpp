#include "GraphicsSet.h"

namespace NzP
{
	GraphicsSet::GraphicsSet(std::string filePath, Nz::Vector2f size) : Nz::RefCounted(), Nz::Resource(), m_texturePath(filePath), m_sizeTiles(size)
	{
		LoadMaterial();
	}

	bool GraphicsSet::SetMaterial(std::string filePath, Nz::Vector2ui size)
	{
		m_texturePath = filePath;
		m_sizeTiles = size;

		return LoadMaterial();
	}

	bool GraphicsSet::LoadMaterial()
	{
		m_material = Nz::Material::New();

		if (m_material->LoadFromFile(m_texturePath))
		{
			m_material->EnableBlending(true);
			m_material->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
			m_material->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
			m_material->EnableDepthWrite(false);

			CreateSpriteList();

			return true;
		}

		return false;
	}

	void GraphicsSet::CreateSpriteList()
	{
		Nz::SpriteRef tempSprite = Nz::Sprite::New(m_material);
		std::size_t nbTileHeight = static_cast<std::size_t>(tempSprite->GetSize().y / m_sizeTiles.y);
		std::size_t nbTileWidth = static_cast<std::size_t>(tempSprite->GetSize().x / m_sizeTiles.x);

		for (std::size_t j = 0; j < nbTileHeight; j++)
		{
			for (std::size_t i = 0; i < nbTileWidth; i++)
			{
				Nz::Rectui textureBox(i*m_sizeTiles.x, j*m_sizeTiles.y, m_sizeTiles.x, m_sizeTiles.y);
				m_spriteList.emplace_back(Nz::Sprite::New(m_material));
				m_spriteList.back()->SetTextureRect(textureBox);
				m_spriteList.back()->SetSize(static_cast<Nz::Vector2f>(m_sizeTiles));
			}
		}
	}

	bool GraphicsSetParams::IsValid() const
	{
		return true;
	}

	bool GraphicsSet::IsValid() const
	{
		return m_impl != nullptr;
	}

	/*bool GraphicsSet::LoadFromFile(const Nz::String& filePath, const GraphicsSetParams& params)
	{
		return GSetLoader::LoadFromFile(this, filePath, params);
	}*/

	bool GraphicsSet::Initialize()
	{
		if (!GSetLibrary::Initialize())
		{
			NazaraError("Failed to initialise library");
			return false;
		}

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
		GSetLibrary::Uninitialize();
	}

	GSetLibrary::LibraryMap GraphicsSet::s_library;
	//GSetLoader::LoaderList GraphicsSet::s_loaders;
	GSetManager::ManagerMap GraphicsSet::s_managerMap;
	GSetManager::ManagerParams GraphicsSet::s_managerParameters;
}