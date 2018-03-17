#include <memory>
#include <bitset>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/wrapper.hpp>

#include <NDK/Application.hpp>
#include <Nazara/Platform/VideoMode.hpp>
#include <Nazara/Renderer/RenderWindow.hpp>
#include <NDK/StateMachine.hpp>

#include "MenuState.h"
#include "GameState.h"
#include "Structure.h"
#include "GraphicsSet.h"
#include "Map.h"
#include "GraphicsComponent.h"
#include "CollidableComponent.h"
#include "NodeComponent.h"
#include "Component.h"

int main()
{
	Ndk::Application application;

	Nz::RenderWindow& mainWindow = application.AddWindow<Nz::RenderWindow>();
	mainWindow.Create(Nz::VideoMode(800, 600, 32), "Test");
	mainWindow.EnableVerticalSync(true);

	NzP::StateData s_states
	{ 
			std::make_shared<NzP::MenuState>(application, mainWindow, s_states),
			std::make_shared<NzP::GameState>(application, mainWindow, s_states)
	};
		
	Ndk::StateMachine monInstance{ s_states.mainStates.menuState };

	///test///
	std::string mapPath = "D:/Programmation_2018/NazaraProject/NazaraProject/Ressources/Maps/VillageBinaryFullSize.map";
	s_states.mainStates.gameState->SetMap(mapPath);

	///end///

		while (application.Run())
		{
			if (!monInstance.Update(application.GetUpdateTime()))
			{
				// Gestion d'erreur si besoin 
				return EXIT_FAILURE; // EXIT_SUCCESS si c'est juste la fin du jeu 
			}
		}

	return EXIT_SUCCESS;
}
