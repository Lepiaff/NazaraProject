#pragma once

#include <memory>
//#include <map>

#include <iostream>

class GameState;
class MenuState;

struct MainStates;
//enum MAP_NAMES;

struct StateData
{
	struct MainStates
	{
		std::shared_ptr<MenuState> menuState;
		std::shared_ptr<GameState> gameState;
	}mainStates;

	/*std::map<MAP_NAMES, std::shared_ptr<Map>> map;

	struct Gui
	{
		std::shared_ptr<Inventory> inventory;
		std::shared_ptr<PlayerStatistiques> playerStatistiques;
	}gui;

	enum MAP_NAMES
	{
		STARTING,
		SECOND,
		THIRD
	};*/

};

