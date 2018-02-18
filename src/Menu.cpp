#include "Menu.h"

Menu::Menu(Ndk::Application& app, Nz::RenderWindow& renderWindow) : AbstractState(app, renderWindow),
		m_view(m_world->CreateEntity()),
		m_canvas(m_world->CreateHandle(), m_renderWindow->GetEventHandler(), m_renderWindow->GetCursorController().CreateHandle()),
		m_backToGameButton(*m_canvas.Add<Ndk::ButtonWidget>()),
		m_newGameButton(*m_canvas.Add<Ndk::ButtonWidget>()),
		m_loadGameButton(*m_canvas.Add<Ndk::ButtonWidget>()),
		m_saveGameButton(*m_canvas.Add<Ndk::ButtonWidget>()),
		m_quitGameButton(*m_canvas.Add<Ndk::ButtonWidget>())
{
	///////////Préparation de la fenetre///////////
	
	Ndk::NodeComponent& nodeViewComponent = m_view->AddComponent<Ndk::NodeComponent>();
	Ndk::CameraComponent& viewer = m_view->AddComponent<Ndk::CameraComponent>();
	viewer.SetTarget(m_renderWindow);
	viewer.SetProjectionType(Nz::ProjectionType_Orthogonal);
	m_canvas.SetSize({ static_cast<float>(m_renderWindow->GetSize().x), static_cast<float>(m_renderWindow->GetSize().y) });
	m_world->GetSystem<Ndk::RenderSystem>().SetDefaultBackground(Nz::ColorBackground::New(Nz::Color(117, 122, 214)));
	Nz::Vector2ui windowSize = m_renderWindow->GetSize();
	
	///////////Bouton Nouvelle partie///////////
	m_backToGameButton.UpdateText(Nz::SimpleTextDrawer::Draw("Reprendre la partie", 50));
	m_backToGameButton.Move(25.f, (windowSize.y / 2) - 2*(m_backToGameButton.GetSize().y + 10), 0.f);
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
	m_quitGameButton.Move(25.f, (windowSize.y / 2) + 2*(m_quitGameButton.GetSize().y + 10), 0.f);
	m_quitGameButton.ResizeToContent();

}

//Méthodes virtuelles de fonctionnement des states

void Menu::Enter(Ndk::StateMachine & fsm)
{
	//Connexion des slot aux signaux des boutons
	Connect();
	
}

void Menu::Leave(Ndk::StateMachine & fsm)
{
	//Déconnexion des slots puisque changement de state
	Disonnect();
}

bool Menu::Update(Ndk::StateMachine & fsm, float elapsedTime)
{
	m_canvas.SetSize({ static_cast<float>(m_renderWindow->GetSize().x), static_cast<float>(m_renderWindow->GetSize().y) });
	m_renderWindow->Display();
	

	return true;
}


//CallBacks liés aux boutons
void Menu::CallBack1(const Ndk::ButtonWidget* button)
{
	std::cout << "Reprendre la partie" << std::endl;
}

void Menu::CallBack2(const Ndk::ButtonWidget * button)
{
	std::cout << "Nouvelle partie" << std::endl;
}

void Menu::CallBack3(const Ndk::ButtonWidget * button)
{
	std::cout << "Charger une partie" << std::endl;
}

void Menu::CallBack4(const Ndk::ButtonWidget * button)
{
	std::cout << "Sauvegarder la partie" << std::endl;
}

void Menu::CallBack5(const Ndk::ButtonWidget * button)
{
	std::cout << "Quitter le jeu" << std::endl;
	//Ndk::Application::Instance()->Quit();
	m_AppParent->Quit();
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