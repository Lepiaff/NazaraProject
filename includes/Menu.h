#pragma once

#include <iostream>

#include <NDK/Prerequisites.hpp>
#include <NDK/BaseWidget.hpp>
#include <NDK/World.hpp>
#include <NDK/Components.hpp>
#include <NDK/Systems.hpp>
#include <NDK/Widgets.hpp>
#include <NDK/Canvas.hpp>
#include <Nazara/Renderer/RenderWindow.hpp>
#include <NDK/Application.hpp>
#include <cstdlib>
#include <iostream>

#include <memory>


#include "AbstractState.h"

class Menu : public AbstractState
{
public:
	Menu(Ndk::Application& app, Nz::RenderWindow& renderWindow);
	~Menu() = default;

	virtual void Enter(Ndk::StateMachine& fsm) ;
	virtual void Leave(Ndk::StateMachine& fsm) ;
	virtual bool Update(Ndk::StateMachine& fsm, float elapsedTime) ;

	void Connect()
	{
		slot1.Connect(m_backToGameButton.OnButtonTrigger, this, &Menu::CallBack1);
		slot2.Connect(m_newGameButton.OnButtonTrigger, this, &Menu::CallBack2);
		slot3.Connect(m_loadGameButton.OnButtonTrigger, this, &Menu::CallBack3);
		slot4.Connect(m_saveGameButton.OnButtonTrigger, this, &Menu::CallBack4);
		slot5.Connect(m_quitGameButton.OnButtonTrigger, this, &Menu::CallBack5);
	}
	void Disonnect()
	{
		slot1.Disconnect();
		slot2.Disconnect();
		slot3.Disconnect();
		slot4.Disconnect();
		slot5.Disconnect();
	}

private:
	Ndk::EntityHandle m_view;
	Ndk::Canvas m_canvas;

	Ndk::ButtonWidget& m_backToGameButton;
	Ndk::ButtonWidget& m_newGameButton;
	Ndk::ButtonWidget& m_loadGameButton;
	Ndk::ButtonWidget& m_saveGameButton;
	Ndk::ButtonWidget& m_quitGameButton;

	//Les NazaraSlot ne peuvent gérer qu'une seule connexion ! (à renommer !!!)
	NazaraSlot(Ndk::ButtonWidget, OnButtonTrigger, slot1);
	NazaraSlot(Ndk::ButtonWidget, OnButtonTrigger, slot2);
	NazaraSlot(Ndk::ButtonWidget, OnButtonTrigger, slot3);
	NazaraSlot(Ndk::ButtonWidget, OnButtonTrigger, slot4);
	NazaraSlot(Ndk::ButtonWidget, OnButtonTrigger, slot5);

	//Les CallBacks qui permettent de réaliser l'action spécifique au signale émis (à renommer !!!)
	void CallBack1(const Ndk::ButtonWidget* button);
	void CallBack2(const Ndk::ButtonWidget* button);
	void CallBack3(const Ndk::ButtonWidget* button);
	void CallBack4(const Ndk::ButtonWidget* button);
	void CallBack5(const Ndk::ButtonWidget* button);

};
