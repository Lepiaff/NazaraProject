#pragma once

#ifndef ABSTRACTSTATE_H
#define ABSTRACTSTATE_H

#include <NDK/Application.hpp>
#include <Nazara/Renderer/RenderWindow.hpp>
#include <NDK/State.hpp>
#include <NDK/StateMachine.hpp>
#include <NDK/World.hpp>

#include "Structure.h"

namespace NzP
{
	class AbstractState : public Ndk::State
	{
	public:
		AbstractState(Ndk::Application& app, Nz::RenderWindow& renderWindow, StateData& states) : Ndk::State(),
			m_states(states),
			m_appParent(app),
			m_world(&m_appParent.AddWorld()),
			m_renderWindow(renderWindow)
		{

		}

		virtual ~AbstractState() = default;


		virtual void Enter(Ndk::StateMachine& fsm) = 0;
		virtual void Leave(Ndk::StateMachine& fsm) = 0;
		virtual bool Update(Ndk::StateMachine& fsm, float elapsedTime) = 0;

		Ndk::WorldHandle& GetWorld() { return m_world; }

	protected:
		Ndk::Application& m_appParent;
		Ndk::WorldHandle m_world;
		Nz::RenderWindow& m_renderWindow;

		StateData& m_states;
	};
}
#endif // !ABSTRACTSTATE_H


