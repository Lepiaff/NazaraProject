#pragma once

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <NDK/State.hpp>
#include <NDK/Entity.hpp>

#include "StateData.h"
#include "MenuState.h"
#include "Map.h"

namespace NzP
{
	class GameState : public Ndk::State
	{
	private:
		//Attrinuts
		StateData & m_stateData;
		NzP::MapRef m_currentMap;
		float m_elapsedTime = 0;
		
	public:
		GameState(StateData& stateData);
		virtual ~GameState() = default;
		
		void Enter(Ndk::StateMachine& fsm) override;
		void Leave(Ndk::StateMachine& fsm) override;
		bool Update(Ndk::StateMachine& fsm, float elapsedTime) override;

		bool SetMap(std::string mapPath);
	};
}
#endif // !GAMESTATE_H