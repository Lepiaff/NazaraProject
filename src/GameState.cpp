#include "GameState.h"

GameState::GameState(Ndk::Application& app, Nz::RenderWindow& renderWindow, StateData & states) : AbstractState(app, renderWindow, states),
		m_view(m_world->CreateEntity())
{
	///////////Préparation de la fenetre///////////
	Ndk::NodeComponent & nodecomponant = m_view->AddComponent<Ndk::NodeComponent>();
	Ndk::CameraComponent & cameracomponant = m_view->AddComponent<Ndk::CameraComponent>();
	cameracomponant.SetTarget(&m_renderWindow);

	cameracomponant.SetProjectionType(Nz::ProjectionType_Orthogonal);

	//paramètres
	m_world->GetSystem<Ndk::RenderSystem>().SetGlobalUp(Nz::Vector3f::Down());
	m_world->GetSystem<Ndk::RenderSystem>().SetDefaultBackground(Nz::ColorBackground::New(Nz::Color(217, 122, 214)));

	//On désactive la vue pour ne pas l'afficher à la construction de l'état
	m_view->Disable();
}

void GameState::Enter(Ndk::StateMachine & fsm)
{
	m_view->Enable();
}

void GameState::Leave(Ndk::StateMachine & fsm)
{
	m_view->Disable();
}

bool GameState::Update(Ndk::StateMachine & fsm, float elapsedTime)
{
	if (m_elapsedTime >= 10)
	{
		m_elapsedTime = 0;
		fsm.ChangeState(m_states.mainStates.menuState);
	}
	else
	{
		m_elapsedTime += elapsedTime;
	}
		
	m_renderWindow.Display();
	return true;
}

void GameState::SetMap(Map * map)
{
	m_currentMap = map;
	LoadMap();
}

void GameState::LoadMap()
{
	m_currentMap->Display();
}

void GameState::ClearMap()
{
	m_currentMap->Hide();
}
