#pragma once

#include <NDK/Application.hpp>
#include <NDK/State.hpp>
#include <NDK/World.hpp>
#include <NDK/Systems.hpp>
#include <Nazara/Graphics.hpp>
#include <Nazara/Renderer.hpp>

class AbstractState : public Ndk::State
{
public:
	AbstractState(Ndk::Application& app, Nz::RenderWindow& renderWindow)
	{ 
		m_AppParent = &app;
		m_world = &(m_AppParent->AddWorld());
		m_world->GetSystem<Ndk::RenderSystem>().SetGlobalUp(Nz::Vector3f::Down());

		m_renderWindow = &renderWindow;

	}

	~AbstractState() = default;


	virtual void Enter(Ndk::StateMachine& fsm) =0 ;
	virtual void Leave(Ndk::StateMachine& fsm) =0 ;
	virtual bool Update(Ndk::StateMachine& fsm, float elapsedTime) =0 ;
	
protected:
	Ndk::Application* m_AppParent;
	Ndk::WorldHandle m_world;
	Nz::RenderWindow* m_renderWindow;

};

