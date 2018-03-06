#pragma once

#include <Nazara/Renderer/RenderWindow.hpp>
#include <NDK/Application.hpp>
#include <NDK/StateMachine.hpp>

#include "AbstractState.h"
#include "GraphicsSet.h"
#include "Map.h"
#include "MenuState.h"

namespace NzP
{
	class GameState : public AbstractState
	{
	public:
		GameState(Ndk::Application& app, Nz::RenderWindow& renderWindow, StateData& states);
		~GameState() = default;

		void Enter(Ndk::StateMachine& fsm) override;
		void Leave(Ndk::StateMachine& fsm) override;
		bool Update(Ndk::StateMachine& fsm, float elapsedTime) override;

		bool SetMap(NzP::Map& map);
		void DisplayMap(const bool state);
		void DisplayLayer(const unsigned int layer, bool display = true);

	protected:
		NzP::Map* m_currentMap;
		std::vector<Ndk::EntityHandle> m_viewList;

		float m_elapsedTime = 0;

	};
}