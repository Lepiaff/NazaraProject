#include "GameState.h"

namespace NzP
{
	GameState::GameState(StateData& stateData) : m_stateData(stateData)
	{

	}

	void GameState::Enter(Ndk::StateMachine& fsm)
	{

	}

	void GameState::Leave(Ndk::StateMachine& fsm)
	{
		if (m_currentMap)
			m_currentMap->HideMap();
	}

	bool GameState::Update(Ndk::StateMachine& fsm, float elapsedTime)
	{
		if (m_elapsedTime >= 5)
		{
			m_elapsedTime = 0;
			fsm.ChangeState(std::make_shared<NzP::MenuState>(m_stateData));
		}
		else
		{
			m_elapsedTime += elapsedTime;
		}
		return true;
	}

	bool GameState::SetMap(std::string mapPath)
	{
		if (m_currentMap)
		{
			m_currentMap->SetPersistent(false);
			m_currentMap->RemoveReference();
		}
		m_currentMap = MapManager::Get(mapPath);
		m_currentMap->SetPersistent(true);
		m_currentMap->DisplayMap(m_stateData.world);
		
		return true;
	}
}