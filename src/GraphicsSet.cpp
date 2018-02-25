#include "GraphicsSet.h"


GraphicsSet::GraphicsSet(std::string filePath, Nz::Vector2f size) : m_texturePath(filePath), m_sizeTiles(size)
{
	LoadMaterial();
}

GraphicsSet::~GraphicsSet()
{
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

	for (std::size_t j = 0 ; j < nbTileHeight ; j++)
	{
		for (std::size_t i = 0 ; i < nbTileWidth ; i++)
		{
			Nz::Rectui textureBox(i*m_sizeTiles.x, j*m_sizeTiles.y, m_sizeTiles.x, m_sizeTiles.y);
			m_spriteList.emplace_back(Nz::Sprite::New(m_material));
			m_spriteList.back()->SetTextureRect(textureBox);
			m_spriteList.back()->SetSize(static_cast<Nz::Vector2f>(m_sizeTiles));
		}
	}
}

