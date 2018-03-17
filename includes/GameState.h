#pragma once

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <NDK/Entity.hpp>

#include "AbstractState.h"
#include "Structure.h"
#include "MenuState.h"
#include "Map.h"

namespace NzP
{
	class GameState : public AbstractState
	{
	public:
		GameState(Ndk::Application& app, Nz::RenderWindow& renderWindow, StateData& states);
		virtual ~GameState() = default;
		
		void Enter(Ndk::StateMachine& fsm) override;
		void Leave(Ndk::StateMachine& fsm) override;
		bool Update(Ndk::StateMachine& fsm, float elapsedTime) override;

		bool SetMap(NzP::MapRef map);
		void DisplayMap(const bool state);
		void DisplayLayer(const unsigned int layer, bool display = true);

	protected:
		NzP::MapRef m_currentMap;
		std::vector<Ndk::EntityHandle> m_viewList;

		float m_elapsedTime = 0;

	};
}
#endif // !GAMESTATE_H