#include "GraphicsSetManager.h"

namespace NzP
{
	bool GraphicsSetManager::Load(std::string& name)
	{
		if (!GSetManager::Get(GRAPHICS_SET_FOLDER_PATH + "/" + name + ".png")->IsValid())
		{
			GraphicsSetRef objectRef;
		
			GSetManager::Register(Nz::String(GRAPHICS_SET_FOLDER_PATH + "/" + name + ".png"), objectRef);
			objectRef->SetMaterial(GRAPHICS_SET_FOLDER_PATH + "/" + name + ".png");
		} 
		return GSetManager::Get(GRAPHICS_SET_FOLDER_PATH + "/" + name + ".png")->IsValid();
			return true;
	}
}