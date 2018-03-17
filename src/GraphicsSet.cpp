#include "GraphicsSet.h"

namespace NzP
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	////M�thodes priv�es///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	///M�thode de cr�ation du sprite demand� par la m�thode GetSprite
	Nz::SpriteRef GraphicsSet::CreateSprite(std::size_t idSprite)
	{
		Nz::String idSpriteString = GetFilePath() + std::to_string(idSprite);

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

	///M�thode de chargement de la ressource
	///Dans ce cas-ci, appelle la m�thode LoadMaterial pour charger la texture
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
		return true;
	}

	///M�thode de chargement de la texture
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

	///////////////////////////////////////////////////////////////////////////////////////////////
	////M�thodes publiques/////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	///M�thode qui v�rifie si le sprite existe d�j� et est archiv�, sinon le fait et le retoutrne
	Nz::SpriteRef GraphicsSet::GetSprite(std::size_t idSprite)
	{
		Nz::String idSpriteString = GetFilePath() + std::to_string(idSprite);
		if (!Nz::SpriteLibrary::Has(idSpriteString))
			return CreateSprite(idSprite);
		return Nz::SpriteLibrary::Get(idSpriteString);
	}

	///M�thode permetant de r�cup�rer l'id d'une tuile selon sa position dans le tileset
	unsigned int GraphicsSet::GetSpriteId(Nz::Vector2f pos)
	{
		Nz::Vector3ui sizeGSet = m_material->GetDiffuseMap()->GetSize();
		//Nz::Vector2f position = std::move(pos);
		pos.x += static_cast<float>(sizeGSet.x) / 2;
		pos.y = -pos.y;

		Nz::Vector2ui posUi{
			static_cast<unsigned int>(pos.x),
			static_cast<unsigned int>(pos.y) };

		unsigned int idTile =
			(posUi.y / s_managerParameters.sizeTiles.y) *
			(sizeGSet.x / s_managerParameters.sizeTiles.x) +
			posUi.x / s_managerParameters.sizeTiles.x;

		return idTile;
	}

	///M�thode de v�rification de la validit� de la ressource
	bool GraphicsSet::IsValid() const
	{
		return true;
	}

	///M�thode de v�rification de la validit� du GraphicsSetParams
	bool GraphicsSetParams::IsValid() const
	{
		if (sizeTiles.x == 0 || sizeTiles.y == 0)
		{
			std::cout << "GraphicsParam invalide ! (Penser � initialiser la taille des tuiles)" << std::endl;
			return false;
		}
		return true;
	}
	
	GSetManager::ManagerMap GraphicsSet::s_managerMap;
	GSetManager::ManagerParams GraphicsSet::s_managerParameters;
}

