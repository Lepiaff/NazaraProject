#include "MenuState.h"

namespace NzP
{
	MenuState::MenuState(StateData& stateData) : m_stateData(stateData)
	{
		
	}

	//Méthodes virtuelles de fonctionnement des states
	void MenuState::Enter(Ndk::StateMachine& fsm)
	{
		//Initialisation du menu
		///Redimensionnement du Canvas
		m_stateData.canvas->SetSize(Nz::Vector2f(
			static_cast<float>(m_stateData.window->GetSize().x),
			static_cast<float>(m_stateData.window->GetSize().y)));

		///paramètre de dimensionnement des boutons
		Nz::Vector2ui windowSize = m_stateData.window->GetSize();

		///Création des boutons du menu
		m_resumeGameButton = m_stateData.canvas->Add<Ndk::ButtonWidget>();
		m_newGameButton = m_stateData.canvas->Add<Ndk::ButtonWidget>();
		m_loadGameButton = m_stateData.canvas->Add<Ndk::ButtonWidget>();
		m_saveGameButton = m_stateData.canvas->Add<Ndk::ButtonWidget>();
		m_quitGameButton = m_stateData.canvas->Add<Ndk::ButtonWidget>();

		///Bouton Nouvelle partie
		m_resumeGameButton->UpdateText(Nz::SimpleTextDrawer::Draw("Reprendre la partie", 50));
		m_resumeGameButton->Move(25.f, (windowSize.y / 2) - 2 * (m_resumeGameButton->GetSize().y + 10), 0.f);
		m_resumeGameButton->ResizeToContent();

		///Bouton Nouvelle partie
		m_newGameButton->UpdateText(Nz::SimpleTextDrawer::Draw("Nouvelle partie", 50));
		m_newGameButton->Move(25.f, (windowSize.y / 2) - m_newGameButton->GetSize().y - 10, 0.f);
		m_newGameButton->ResizeToContent();

		///Bouton Nouvelle partie
		m_loadGameButton->UpdateText(Nz::SimpleTextDrawer::Draw("Charger une partie", 50));
		m_loadGameButton->Move(25.f, (windowSize.y / 2) + 0.f, 0.f);
		m_loadGameButton->ResizeToContent();

		///Bouton Nouvelle partie
		m_saveGameButton->UpdateText(Nz::SimpleTextDrawer::Draw("Sauvegarder la partie", 50));
		m_saveGameButton->Move(25.f, (windowSize.y / 2) + m_saveGameButton->GetSize().y + 10, 0.f);
		m_saveGameButton->ResizeToContent();

		///Bouton Nouvelle partie
		m_quitGameButton->UpdateText(Nz::SimpleTextDrawer::Draw("Quitter le jeu", 50));
		m_quitGameButton->Move(25.f, (windowSize.y / 2) + 2 * (m_quitGameButton->GetSize().y + 10), 0.f);
		m_quitGameButton->ResizeToContent();

		//Connexion des slots aux signaux des boutons
		Connect();
	}

	void MenuState::Leave(Ndk::StateMachine& fsm)
	{
		//Préparation de la sortie du menu
		///On détruit les boutons pour qu'ils n'existent plus dans le canvas
		m_resumeGameButton->Destroy();
		m_newGameButton->Destroy();
		m_loadGameButton->Destroy();
		m_saveGameButton->Destroy();
		m_quitGameButton->Destroy();

		///Déconnexion des slots puisque changement de state
		Disonnect();
	}

	bool MenuState::Update(Ndk::StateMachine& fsm, float elapsedTime)
	{
		m_stateData.canvas->SetSize(Nz::Vector2f(
			static_cast<float>(m_stateData.window->GetSize().x),
			static_cast<float>(m_stateData.window->GetSize().y)));

		if (m_newGamePressed)
		{
			///std::string mapPath = "D:/Programmation_2018/NazaraProject/NazaraProject/Ressources/Maps/VillageBinaryFullSize.map";
			std::string mapPath = "D:/Programmation_2018/NazaraProject/NazaraProject/Ressources/Maps/VillageBinary.map";
			auto gameState = std::make_shared<NzP::GameState>(m_stateData);
			gameState->SetMap(mapPath);
			fsm.ChangeState(gameState);
		}

		return true;
	}

	void MenuState::Connect()
	{
		resumeGameSlot.Connect(m_resumeGameButton->OnButtonTrigger, this, &MenuState::resumeGameCallBack);
		newGameSlot.Connect(m_newGameButton->OnButtonTrigger, this, &MenuState::newGameCallBack);
		loadGameSlot.Connect(m_loadGameButton->OnButtonTrigger, this, &MenuState::loadGameCallBack);
		saveGameSlot.Connect(m_saveGameButton->OnButtonTrigger, this, &MenuState::saveGameCallBack);
		quitGameSlot.Connect(m_quitGameButton->OnButtonTrigger, this, &MenuState::quitGameCallBack);
	}

	void MenuState::Disonnect()
	{
		resumeGameSlot.Disconnect();
		newGameSlot.Disconnect();
		loadGameSlot.Disconnect();
		saveGameSlot.Disconnect();
		quitGameSlot.Disconnect();
	}
	
	//CallBacks liés aux boutons
	void MenuState::resumeGameCallBack(const Ndk::ButtonWidget* button)
	{
		std::cout << "Reprendre la partie" << std::endl;
		m_resumeGamePressed = true;
	}

	void MenuState::newGameCallBack(const Ndk::ButtonWidget* button)
	{
		std::cout << "Nouvelle partie" << std::endl;
		m_newGamePressed = true;
	}

	void MenuState::loadGameCallBack(const Ndk::ButtonWidget* button)
	{
		std::cout << "Charger une partie" << std::endl;
		m_loadGamePressed = true;
	}

	void MenuState::saveGameCallBack(const Ndk::ButtonWidget* button)
	{
		std::cout << "Sauvegarder la partie" << std::endl;
		m_saveGamePressed = true;
	}

	void MenuState::quitGameCallBack(const Ndk::ButtonWidget* button)
	{
		std::cout << "Quitter le jeu" << std::endl;
		Ndk::Application::Instance()->Quit();
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
