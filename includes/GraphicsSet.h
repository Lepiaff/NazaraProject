#pragma once

#ifndef GRAPHICSSET_H
#define GRAPHICSSET_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <utility>

#include <Nazara/Core/MovablePtr.hpp>
#include <Nazara/Graphics/Sprite.hpp>
#include <Nazara/Graphics/Material.hpp>
#include <Nazara/Core/HandledObject.hpp>
#include <Nazara/Core/RefCounted.hpp>
#include <Nazara/Core/String.hpp>
#include <Nazara/Core/ResourceParameters.hpp>
#include <Nazara/Core/ResourceManager.hpp>
#include <Nazara/Core/Resource.hpp>
#include <Nazara/Core/ObjectRef.hpp>
#include <Nazara/Core/ObjectLibrary.hpp>
#include <Nazara/Core/ResourceLoader.hpp>


namespace NzP
{
	struct GraphicsSetParams : public Nz::ResourceParameters
	{
		friend class GraphicsSet;
		GraphicsSetParams() = default;
		Nz::Vector2ui sizeTiles{32, 32 };
		bool IsValid() const; // vérifie que tous les paramètres sont présents et valide pour initialiser le Gset
	};

	class GraphicsSet;
	
	using GraphicsSetConstRef = Nz::ObjectRef<const GraphicsSet>;
	using GSetLibrary = Nz::ObjectLibrary<GraphicsSet>;
	using GSetLoader = Nz::ResourceLoader<GraphicsSet, GraphicsSetParams>;
	using GSetManager = Nz::ResourceManager<GraphicsSet, GraphicsSetParams>;
	using GraphicsSetRef = Nz::ObjectRef<GraphicsSet>;

	struct GraphicsSetImpl {};


	//Classe
	class GraphicsSet : public Nz::RefCounted, public Nz::Resource
	{
		friend GSetLibrary;
		friend GSetLoader;
		friend GSetManager;
		friend class Utility;

	public:
		GraphicsSet() = default;
		GraphicsSet(const Nz::String& filePath, const GraphicsSetParams& params = GraphicsSetParams());
		~GraphicsSet() = default;

		Nz::SpriteRef GetSprite(std::size_t idSprite);
		std::vector<Nz::SpriteRef>& GetSpriteList() { return spriteList; }
		unsigned int GetSpriteId(Nz::Rectf textureRect);

		
		bool IsValid() const;

		template<typename... Args>
		static GraphicsSetRef New(Args&&... args)
		{
			std::unique_ptr<GraphicsSet> object(new GraphicsSet(std::forward<Args>(args)...));
			object->SetPersistent(false);

			return object.release();
		}

	private:
		bool LoadFromFile(const Nz::String& filePath, const GraphicsSetParams& params = GSetManager::GetDefaultParameters());

		bool LoadMaterial();
		void CreateSpriteList();

		//Manager

		static bool Initialize();
		static void Uninitialize();

		Nz::MovablePtr<GraphicsSetImpl> m_impl = nullptr;
		static GSetLibrary::LibraryMap s_library;
		static GSetLoader::LoaderList s_loaders;
		static GSetManager::ManagerMap s_managerMap;
		static GSetManager::ManagerParams s_managerParameters;
		
		//Attributs
		Nz::MaterialRef material;
		std::vector<Nz::SpriteRef> spriteList;
	};


	

}
#endif // GRAPHICSSET_H

