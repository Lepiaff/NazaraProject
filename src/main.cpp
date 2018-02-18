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

#include "Game.h"
#include "Menu.h"

int main()
{
	Ndk::Application application;

	Nz::RenderWindow& mainWindow = application.AddWindow<Nz::RenderWindow>();
	mainWindow.Create(Nz::VideoMode(800, 600, 32), "Test");
	mainWindow.EnableVerticalSync(true);

	auto menuStat{ std::make_shared<Menu>(application, mainWindow) };
	auto gameStat{ std::make_shared<Game>(application, mainWindow) };

	Ndk::StateMachine monInstance { gameStat };

	monInstance.PushState(menuStat);
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