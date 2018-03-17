#include "GraphicsSet.h"

namespace NzP
{
	GraphicsSet::GraphicsSet(const Nz::String& filePath, const GraphicsSetParams& params) : Nz::RefCounted(), Nz::Resource()
	{
		Initialize();
		SetFilePath(filePath);
		s_managerParameters = params;
		LoadMaterial();
	}

	unsigned int GraphicsSet::GetSpriteId(Nz::Vector2f pos)
	{
		//A impl�menter
		Nz::Vector3ui sizeGSet = m_material->GetDiffuseMap()->GetSize();
		Nz::Vector2f position = std::move(pos);
		position.x += static_cast<float>(sizeGSet.x) / 2;
		position.y = -position.y;

		Nz::Vector2ui posUi{
			static_cast<unsigned int>(position.x),
			static_cast<unsigned int>(position.y) };

		unsigned int idTile =
			(posUi.y / s_managerParameters.sizeTiles.y) *
			(sizeGSet.x / s_managerParameters.sizeTiles.x) +
			posUi.x / s_managerParameters.sizeTiles.x;

		return idTile;
	}

	Nz::SpriteRef GraphicsSet::GetSprite(std::size_t idSprite)
	{
		Nz::String idSpriteString = static_cast<Nz::String>(idSprite);
		if (!Nz::SpriteLibrary::Has(idSpriteString))
		{
			return std::move(CreateSprite(idSprite));
		}
		return Nz::SpriteLibrary::Get(idSpriteString);
	}

	Nz::SpriteRef GraphicsSet::CreateSprite(std::size_t idSprite)
	{
		Nz::String idSpriteString = static_cast<Nz::String>(idSprite);

		Nz::Vector3ui textureSize = m_material->GetDiffuseMap()->GetSize();
		std::size_t nbTileHeight = textureSize.y / s_managerParameters.sizeTiles.y;
		std::size_t nbTileWidth = textureSize.x / s_managerParameters.sizeTiles.x;

		std::size_t heightIndex = idSprite / nbTileWidth;
		std::size_t widthIndex = idSprite % nbTileWidth;

		Nz::Rectui textureBox(
			widthIndex * s_managerParameters.sizeTiles.x,
			heightIndex*s_managerParameters.sizeTiles.y,
			s_managerParameters.sizeTiles.x,
			s_managerParameters.sizeTiles.y);

		Nz::SpriteLibrary::Register(idSpriteString, Nz::Sprite::New(m_material));
		Nz::SpriteRef spriteRef = Nz::SpriteLibrary::Get(idSpriteString);
		spriteRef->SetTextureRect(textureBox);
		spriteRef->SetSize(static_cast<Nz::Vector2f>(s_managerParameters.sizeTiles));
		return std::move(spriteRef);
	}

	bool GraphicsSet::LoadMaterial()
	{
		if (!s_managerParameters.IsValid())
			return false;

		m_material = Nz::Material::New();
		if (m_material->LoadFromFile(GetFilePath()))
		{
			m_material->EnableBlending(true);
			m_material->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
			m_material->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
			m_material->EnableDepthWrite(false);

			return true;
		}
		return false;
	}

	bool GraphicsSetParams::IsValid() const
	{
		if (sizeTiles.x == 0 || sizeTiles.y == 0)
		{
			std::cout << "GraphicsParam invalide ! (Penser � initialiser la taille des tuiles)" << std::endl;
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
	}

	//M�thode de chargement de la ressource
	//Dans ce cas-ci, appelle la m�thode LoadMaterial pour charger la texture
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
		//GSetManager::Register(filePath, this);
		//std::cout << "GraphicsSet registered" << std::endl;
		return true;
	}

	GSetManager::ManagerMap GraphicsSet::s_managerMap;
	GSetManager::ManagerParams GraphicsSet::s_managerParameters;
}

