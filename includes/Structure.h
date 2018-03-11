#pragma once

#include <memory>
#include <iostream>

namespace NzP
{
	struct MainStates;
	class GameState;
	class MenuState;

	struct StateData
	{
		struct MainStates
		{
			std::shared_ptr<MenuState> menuState;
			std::shared_ptr<GameState> gameState;
		}mainStates;
	};
}