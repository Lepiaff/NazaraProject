#pragma once

#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <memory>

#include <NDK/Widgets/ButtonWidget.hpp>
#include <NDK/Components/NodeComponent.hpp>
#include <NDK/Components/CameraComponent.hpp>
#include <NDK/Systems/RenderSystem.hpp>
#include <nazara/Graphics/ColorBackground.hpp>

#include <NDK/StateMachine.hpp>

#include "StateData.h"
#include "GameState.h"
#include "GraphicsSet.h"

namespace NzP
{
	class MenuState : public Ndk::State
	{
	private:
		//Attributes
		StateData & m_stateData;

		bool m_resumeGamePressed = false;
		bool m_newGamePressed = false;
		bool m_loadGamePressed = false;
		bool m_saveGamePressed = false;
		
		Ndk::ButtonWidget* m_resumeGameButton;
		Ndk::ButtonWidget* m_newGameButton;
		Ndk::ButtonWidget* m_loadGameButton;
		Ndk::ButtonWidget* m_saveGameButton;
		Ndk::ButtonWidget* m_quitGameButton;

		//Méthodes privées
		void Connect();
		void Disonnect();

		//Les NazaraSlot ne peuvent gérer qu'une seule connexion !
		NazaraSlot(Ndk::ButtonWidget, OnButtonTrigger, resumeGameSlot);
		NazaraSlot(Ndk::ButtonWidget, OnButtonTrigger, newGameSlot);
		NazaraSlot(Ndk::ButtonWidget, OnButtonTrigger, loadGameSlot);
		NazaraSlot(Ndk::ButtonWidget, OnButtonTrigger, saveGameSlot);
		NazaraSlot(Ndk::ButtonWidget, OnButtonTrigger, quitGameSlot);

		//Les CallBacks qui permettent de réaliser l'action spécifique au signale émis
		void resumeGameCallBack(const Ndk::ButtonWidget* button);
		void newGameCallBack(const Ndk::ButtonWidget* button);
		void loadGameCallBack(const Ndk::ButtonWidget* button);
		void saveGameCallBack(const Ndk::ButtonWidget* button);
		void quitGameCallBack(const Ndk::ButtonWidget* button);

	public:
		MenuState(StateData& stateData);
		virtual ~MenuState() = default;

		//Méthodes publiques
		virtual void Enter(Ndk::StateMachine& fsm) override;
		virtual void Leave(Ndk::StateMachine& fsm) override;
		virtual bool Update(Ndk::StateMachine& fsm, float elapsedTime) override;
	};
}
#endif // !MENUSTATE_H