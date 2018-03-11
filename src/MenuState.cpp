#include "MenuState.h"

namespace NzP
{
	MenuState::MenuState(Ndk::Application& app, Nz::RenderWindow& renderWindow, StateData& states) : AbstractState(app, renderWindow, states), 
		m_view(m_world->CreateEntity()),
		m_canvas(m_world->CreateHandle(), m_renderWindow.GetEventHandler(), m_renderWindow.GetCursorController().CreateHandle()),
		m_backToGameButton(*m_canvas.Add<Ndk::ButtonWidget>()),
		m_newGameButton(*m_canvas.Add<Ndk::ButtonWidget>()),
		m_loadGameButton(*m_canvas.Add<Ndk::ButtonWidget>()),
		m_saveGameButton(*m_canvas.Add<Ndk::ButtonWidget>()),
		m_quitGameButton(*m_canvas.Add<Ndk::ButtonWidget>())

	{
		///////////Préparation de la fenetre///////////

		Ndk::NodeComponent & nodecomponant = m_view->AddComponent<Ndk::NodeComponent>();
		Ndk::CameraComponent & cameracomponant = m_view->AddComponent<Ndk::CameraComponent>();
		cameracomponant.SetTarget(&m_renderWindow);
		cameracomponant.SetProjectionType(Nz::ProjectionType_Orthogonal);

		//Redimensionnement du Canvas
		m_canvas.SetSize({ static_cast<float>(m_renderWindow.GetSize().x), static_cast<float>(m_renderWindow.GetSize().y) });

		//paramètres
		m_world->GetSystem<Ndk::RenderSystem>().SetGlobalUp(Nz::Vector3f::Down());
		Nz::Vector2ui windowSize = m_renderWindow.GetSize();
		m_world->GetSystem<Ndk::RenderSystem>().SetDefaultBackground(Nz::ColorBackground::New(Nz::Color(117, 122, 214)));

		//On désactive la vue pour ne pas l'afficher à la construction de l'état
		m_view->Disable();

		///////////Bouton Nouvelle partie///////////
		m_backToGameButton.UpdateText(Nz::SimpleTextDrawer::Draw("Reprendre la partie", 50));
		m_backToGameButton.Move(25.f, (windowSize.y / 2) - 2 * (m_backToGameButton.GetSize().y + 10), 0.f);
		m_backToGameButton.ResizeToContent();

		///////////Bouton Nouvelle partie///////////
		m_newGameButton.UpdateText(Nz::SimpleTextDrawer::Draw("Nouvelle partie", 50));
		m_newGameButton.Move(25.f, (windowSize.y / 2) - m_newGameButton.GetSize().y - 10, 0.f);
		m_newGameButton.ResizeToContent();

		///////////Bouton Nouvelle partie///////////
		m_loadGameButton.UpdateText(Nz::SimpleTextDrawer::Draw("Charger une partie", 50));
		m_loadGameButton.Move(25.f, (windowSize.y / 2) + 0.f, 0.f);
		m_loadGameButton.ResizeToContent();

		///////////Bouton Nouvelle partie///////////
		m_saveGameButton.UpdateText(Nz::SimpleTextDrawer::Draw("Sauvegarder la partie", 50));
		m_saveGameButton.Move(25.f, (windowSize.y / 2) + m_saveGameButton.GetSize().y + 10, 0.f);
		m_saveGameButton.ResizeToContent();

		///////////Bouton Nouvelle partie///////////
		m_quitGameButton.UpdateText(Nz::SimpleTextDrawer::Draw("Quitter le jeu", 50));
		m_quitGameButton.Move(25.f, (windowSize.y / 2) + 2 * (m_quitGameButton.GetSize().y + 10), 0.f);
		m_quitGameButton.ResizeToContent();
	}

	//Méthodes virtuelles de fonctionnement des states

	void MenuState::Enter(Ndk::StateMachine& fsm)
	{
		m_view->Enable();

		//Connexion des slot aux signaux des boutons
		Connect();
	}

	void MenuState::Leave(Ndk::StateMachine& fsm)
	{
		m_view->Disable();

		//Déconnexion des slots puisque changement de state
		Disonnect();
	}

	bool MenuState::Update(Ndk::StateMachine& fsm, float elapsedTime)
	{
		if (m_changeState)
		{
			m_view->Disable();
			fsm.ChangeState(m_states.mainStates.gameState);
			m_changeState = false;
		}
		else
		{
			m_canvas.SetSize({ static_cast<float>(m_renderWindow.GetSize().x), static_cast<float>(m_renderWindow.GetSize().y) });
			m_renderWindow.Display();
		}
		return true;
	}


	//CallBacks liés aux boutons
	void MenuState::CallBack1(const Ndk::ButtonWidget* button)
	{
		std::cout << "Reprendre la partie" << std::endl;
	}

	void MenuState::CallBack2(const Ndk::ButtonWidget* button)
	{
		std::cout << "Nouvelle partie" << std::endl;
		m_changeState = true;
	}

	void MenuState::CallBack3(const Ndk::ButtonWidget* button)
	{
		std::cout << "Charger une partie" << std::endl;
	}

	void MenuState::CallBack4(const Ndk::ButtonWidget* button)
	{
		std::cout << "Sauvegarder la partie" << std::endl;
	}

	void MenuState::CallBack5(const Ndk::ButtonWidget* button)
	{
		std::cout << "Quitter le jeu" << std::endl;
		//Ndk::Application::Instance()->Quit();
		m_appParent.Quit();
	}
}


	///Exemple signal/slot

	///Connexion avec NazaraSlot (dans le header) et fonction membre CallBack
	//slot.Connect(m_backToGameButton.OnButtonTrigger, this, &Menu::CallBack);

	///Connexion avec NazaraSlot (dans le header) sans fonction
	/*slot.Connect(m_backToGameButton.OnButtonTrigger,
	[this](const Ndk::ButtonWidget* button)
	{
	std::cout << "Reprendre la partie" << std::endl;
	});*/

	///Connexion basique
	/*m_backToGameButton.OnButtonTrigger.Connect([this](const Ndk::ButtonWidget* button)
	{
	std::cout << "Reprendre la partie" << std::endl;
	Callback(button);
	});*/
