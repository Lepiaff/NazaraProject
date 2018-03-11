#pragma once

#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <NDK/Canvas.hpp>
#include <NDK/Entity.hpp>
#include <NDK/Widgets/ButtonWidget.hpp>
#include <NDK/Components/NodeComponent.hpp>
#include <NDK/Components/CameraComponent.hpp>
#include <NDK/Systems/RenderSystem.hpp>
#include <nazara/Graphics/ColorBackground.hpp>


#include "AbstractState.h"
#include "Structure.h"
#include "GameState.h"
//#include "GraphicsSet.h"

namespace NzP
{
	class MenuState : public AbstractState
	{
	public:
		MenuState(Ndk::Application& app, Nz::RenderWindow& renderWindow, StateData& states);
		virtual ~MenuState() = default;

		virtual void Enter(Ndk::StateMachine& fsm) override;
		virtual void Leave(Ndk::StateMachine& fsm) override;
		virtual bool Update(Ndk::StateMachine& fsm, float elapsedTime) override;

		void Connect()
		{
			slot1.Connect(m_backToGameButton.OnButtonTrigger, this, &MenuState::CallBack1);
			slot2.Connect(m_newGameButton.OnButtonTrigger, this, &MenuState::CallBack2);
			slot3.Connect(m_loadGameButton.OnButtonTrigger, this, &MenuState::CallBack3);
			slot4.Connect(m_saveGameButton.OnButtonTrigger, this, &MenuState::CallBack4);
			slot5.Connect(m_quitGameButton.OnButtonTrigger, this, &MenuState::CallBack5);
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

		bool m_changeState{ false };

		Ndk::Canvas m_canvas;
		Ndk::EntityHandle m_view;

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
}
#endif // !MENUSTATE_H