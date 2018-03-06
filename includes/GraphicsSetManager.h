#pragma once

#ifndef GRAPHICSSETMANAGER_H
#define GRAPHICSSETMANAGER_H

#include <string>
#include <map>

#include <Nazara/Graphics.hpp>
#include <Nazara/Core/ObjectRef.hpp>
#include <Nazara/Core/Resource.hpp>
#include <Nazara/Core.hpp>
#include <Nazara/Core/ResourceManager.hpp>

#include "GraphicsSet.h"

const std::string GRAPHICS_SET_FOLDER_PATH = "D:/Programmation_2018/NazaraProject/NazaraProject/Ressources/Tilesets/32x32";

namespace NzP
{
	
	class GraphicsSetManager
	{
	public:
		GraphicsSetManager() = default;
		~GraphicsSetManager() = default;

		bool Load(std::string& name);


	private:

	};

}
#endif //GRAPHICSSETMANAGER_H