#include "GraphicsSetManager.h"

bool GraphicsSetManager::Load(std::string & name)
{
	if (!Exist(name))
	{
		m_GraphicsSetMap[name] = GraphicsSet();
	}
		return m_GraphicsSetMap[name].SetMaterial(GRAPHICS_SET_FOLDER_PATH + "/" + name + ".png");

	return true;
}

bool GraphicsSetManager::Exist(const std::string & name)
{
	if (m_GraphicsSetMap.find(name) != m_GraphicsSetMap.end())
		return true;
	return false;
}
