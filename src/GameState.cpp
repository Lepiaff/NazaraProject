#include "GameState.h"

namespace NzP
{
	GameState::GameState(Ndk::Application& app, Nz::RenderWindow& renderWindow, StateData& states) : AbstractState(app, renderWindow, states)
	{

	}

	void GameState::Enter(Ndk::StateMachine& fsm)
	{
		DisplayMap(true);
	}

	void GameState::Leave(Ndk::StateMachine& fsm)
	{
		DisplayMap(false);
	}

	bool GameState::Update(Ndk::StateMachine& fsm, float elapsedTime)
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

	bool GameState::SetMap(NzP::Map& map)
	{
		if (m_currentMap)
			return false;

		m_currentMap = &map;

		for (auto layer : m_currentMap->GetLayers())
		{
			m_viewList.emplace_back(layer->CreateEntity());

			///////////Préparation de la fenetre///////////
			Ndk::NodeComponent & nodecomponant = m_viewList.back()->AddComponent<Ndk::NodeComponent>();
			Ndk::CameraComponent & cameraComponant = m_viewList.back()->AddComponent<Ndk::CameraComponent>();
			cameraComponant.SetTarget(&m_renderWindow);

			cameraComponant.SetProjectionType(Nz::ProjectionType_Orthogonal);

			//paramètres
			layer->GetSystem<Ndk::RenderSystem>().SetGlobalUp(Nz::Vector3f::Down());
			layer->GetSystem<Ndk::RenderSystem>().SetDefaultBackground(Nz::ColorBackground::New(Nz::Color(217, 122, 214)));
		}
		//On desactive la map pour le moment
		DisplayMap(false);
		return true;
	}

	void GameState::DisplayMap(const bool state)
	{
		for (auto view : m_viewList)
		{
			if (state)
			{
				view->Enable();
			}
			else {
				view->Disable();
			}
		}
		//m_currentMap->Display(state); // désactive chaque entité de la map....
	}

	void GameState::DisplayLayer(const unsigned int layer, bool display)
	{
		if (display)
		{
			m_viewList[layer]->Enable();
		}
		else {
			m_viewList[layer]->Disable();
		}

	}
}