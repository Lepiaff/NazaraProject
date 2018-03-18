#pragma once

#ifndef STATEDATA_H
#define STATEDATA_H

#include <NDK/Application.hpp>
#include <Nazara/Renderer/RenderWindow.hpp>
#include <NDK/Canvas.hpp>
#include <NDK/Entity.hpp>
#include <NDK/World.hpp>

namespace NzP
{
	///Package contenant les �l�ments n�c�ssaire au fonctionnement des diff�rents states
	struct StateData
	{
		Ndk::Application* app;
		Nz::RenderWindow* window;
		Ndk::Canvas* canvas;
		Ndk::EntityHandle camera;
		Ndk::WorldHandle world;
	};
}
#endif