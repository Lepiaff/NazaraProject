#pragma once

#include<string>
#include<iostream>

#include<Nazara/Graphics/Sprite.hpp>
#include<Nazara/Graphics/Material.hpp>

class GraphicsSet
{
public:
	GraphicsSet() { ; }
	GraphicsSet(std::string filePath, Nz::Vector2f size = Nz::Vector2f(32, 32));
	~GraphicsSet();

	//Set
	bool SetMaterial(std::string filePath, Nz::Vector2f size = Nz::Vector2f(32, 32));

	//Get
	Nz::SpriteRef GetSprite(std::size_t idSprite) { return (idSprite < m_spriteList.size() ? m_spriteList[idSprite] : Nz::SpriteRef()); }
	std::vector<Nz::SpriteRef> & GetSpriteList() { return m_spriteList; }


protected:
	bool LoadMaterial();
	void CreateSpriteList();

	std::string m_texturePath;
	Nz::Vector2f m_sizeTiles;
	Nz::MaterialRef m_material;
	std::vector<Nz::SpriteRef> m_spriteList;

};

