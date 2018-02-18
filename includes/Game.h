#pragma once

#include "AbstractState.h"

class Game : public AbstractState
{
public:
	Game(Ndk::Application& app, Nz::RenderWindow& renderWindow) : AbstractState(app, renderWindow) {};
	~Game() = default;

	virtual void Enter(Ndk::StateMachine& fsm) ;
	virtual void Leave(Ndk::StateMachine& fsm) ;
	virtual bool Update(Ndk::StateMachine& fsm, float elapsedTime) ;


};

