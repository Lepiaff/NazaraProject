#include <memory>

#include <Nazara/Graphics.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>
#include <NDK/Application.hpp>
#include <NDK/Components.hpp>
#include <NDK/Systems.hpp>
#include <NDK/World.hpp>
#include <iostream>

#include <NDK/State.hpp>
#include <NDK/StateMachine.hpp>

#include "GameState.h"
#include "MenuState.h"
#include "Structure.h"
#include "GraphicsSet.h"

#include "MapManager.h"

int main()
{
	Ndk::Application application;

	Nz::RenderWindow& mainWindow = application.AddWindow<Nz::RenderWindow>();
	mainWindow.Create(Nz::VideoMode(800, 600, 32), "Test");
	mainWindow.EnableVerticalSync(true);

	StateData s_states{ 
			std::make_shared<MenuState>(application, mainWindow, s_states),
			std::make_shared<GameState>(application, mainWindow, s_states)
	};
		
	Ndk::StateMachine monInstance{ s_states.mainStates.menuState };

	///test///
	GraphicsSetManager graphicsSetManager;
	MapManager mapManager(application, graphicsSetManager);
	
	if (mapManager.Exist("Village"))
	{
		s_states.mainStates.gameState->SetMap(&mapManager.GetMap("Village"));
	}
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
