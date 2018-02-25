#pragma once

#include <iostream>
#include <cstdlib>
#include <memory>

#include <NDK/Prerequisites.hpp>
#include <NDK/BaseWidget.hpp>
#include <NDK/World.hpp>
#include <NDK/Components.hpp>
#include <NDK/Systems.hpp>
#include <NDK/Widgets.hpp>
#include <NDK/Canvas.hpp>
#include <Nazara/Renderer/RenderWindow.hpp>
#include <NDK/Application.hpp>
#include <NDK/StateMachine.hpp>

#include "AbstractState.h"
#include "GraphicsSet.h"
#include "Map.h"

#include "MenuState.h"

class GameState : public AbstractState
{
	public:
		GameState(Ndk::Application& app, Nz::RenderWindow& renderWindow, StateData & states);
		~GameState() = default;

		void Enter(Ndk::StateMachine& fsm) override;
		void Leave(Ndk::StateMachine& fsm) override;
		bool Update(Ndk::StateMachine& fsm, float elapsedTime) override;

		void SetMap(Map * map);
		void ClearMap();
		void LoadMap();

	protected:
		Map * m_currentMap = nullptr;
		Ndk::EntityHandle m_view;

		float m_elapsedTime = 0;
	
};

