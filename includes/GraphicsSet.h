#pragma once

#ifndef GRAPHICSSET_H
#define GRAPHICSSET_H

#include<string>
#include<iostream>
#include<unordered_map>
#include <memory>
#include <utility>

#include <Nazara/Core/MovablePtr.hpp>
#include<Nazara/Graphics/Sprite.hpp>
#include<Nazara/Graphics/Material.hpp>
#include<Nazara/Core/HandledObject.hpp>
#include<Nazara/Core/RefCounted.hpp>
#include<Nazara/Core/String.hpp>
#include<Nazara/Core/ResourceParameters.hpp>
#include<Nazara/Core/ResourceManager.hpp>
#include<Nazara/Core/Resource.hpp>
#include <Nazara/Core/ObjectRef.hpp>
#include <Nazara/Core/ObjectLibrary.hpp>
#include <Nazara/Core/ResourceLoader.hpp>


namespace NzP
{
	struct GraphicsSetParams : public Nz::ResourceParameters 
	{
		bool IsValid() const;
	};

	class GraphicsSet;

	using GraphicsSetConstRef = Nz::ObjectRef<const GraphicsSet>;
	using GSetLibrary = Nz::ObjectLibrary<GraphicsSet>;
	//using GSetLoader = Nz::ResourceLoader<GraphicsSet, GraphicsSetParams>;
	using GSetManager = Nz::ResourceManager<GraphicsSet, GraphicsSetParams>;
	using GraphicsSetRef = Nz::ObjectRef<GraphicsSet>;

	struct GraphicsSetImpl {};

	class GraphicsSet : public Nz::RefCounted, public Nz::Resource
	{
		friend GSetLibrary;
		//friend GSetLoader;
		friend GSetManager;
		friend class Utility;

	public:
		GraphicsSet() = default;
		GraphicsSet(std::string filePath, Nz::Vector2f size = Nz::Vector2f(32, 32));
		~GraphicsSet() = default;

		bool SetMaterial(std::string filePath, Nz::Vector2ui size = Nz::Vector2ui(32, 32));

		Nz::SpriteRef GetSprite(std::size_t idSprite) { return (idSprite < m_spriteList.size() ? m_spriteList[idSprite] : Nz::SpriteRef()); }
		std::vector<Nz::SpriteRef>& GetSpriteList() { return m_spriteList; }

		//bool LoadFromFile(const Nz::String& filePath, const GraphicsSetParams& params);
		bool LoadFromFile(const Nz::String& filePath, const GraphicsSetParams& params = GraphicsSetParams())
		{
			m_texturePath = filePath.ToStdString();
			//m_sizeTiles = size;

			return LoadMaterial();
		}

		bool IsValid() const;

		template<typename... Args>
		static GraphicsSetRef New(Args&&... args)
		{
			std::unique_ptr<GraphicsSet> object(new GraphicsSet(std::forward<Args>(args)...));
			object->SetPersistent(false);

			return object.release();
		}

	private:
		bool LoadMaterial();
		void CreateSpriteList();

		std::string m_texturePath;
		Nz::Vector2ui m_sizeTiles;
		Nz::MaterialRef m_material;
		std::vector<Nz::SpriteRef> m_spriteList;


		//Manager

		static bool Initialize();
		static void Uninitialize();

		Nz::MovablePtr<GraphicsSetImpl> m_impl = nullptr;

		static GSetLibrary::LibraryMap s_library;
		//static GSetLoader::LoaderList s_loaders;
		static GSetManager::ManagerMap s_managerMap;
		static GSetManager::ManagerParams s_managerParameters;
		
	};
}
#endif // GRAPHICSSET_H