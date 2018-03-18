#include <memory>

#include <NDK/Application.hpp>
#include <NDK/StateMachine.hpp>

#include <Nazara/Platform/VideoMode.hpp>
#include <Nazara/Renderer/RenderWindow.hpp>

#include "MenuState.h"
#include "StateData.h"


static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;
static std::string WINDOW_TITLE = "Redemarrage";

int main()
{
	//Initialisation de l'application
	///Permet d'initialier tous les modules de Nazara
	Ndk::Application application;

	//Initialisation de la fen�tre de rendu
	///
	Nz::RenderWindow& mainWindow = application.AddWindow<Nz::RenderWindow>();
	mainWindow.Create(Nz::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), WINDOW_TITLE);
	mainWindow.EnableVerticalSync(true);
	mainWindow.EnableCloseOnQuit(false);

	//Cr�ation d'un world dans l'application
	///
	Ndk::World& world = application.AddWorld();
	world.GetSystem<Ndk::RenderSystem>().SetDefaultBackground(Nz::ColorBackground::New(Nz::Color(117, 122, 214)));
	world.GetSystem<Ndk::RenderSystem>().SetGlobalUp(Nz::Vector3f::Down());

	//Cr�ation d'une cam�ra dans le world pour repr�senter la vue
	///et param�trage de la vue 2d
	const Ndk::EntityHandle& camera = world.CreateEntity();
	Ndk::CameraComponent& cameraComponent = camera->AddComponent<Ndk::CameraComponent>();
	cameraComponent.SetProjectionType(Nz::ProjectionType_Orthogonal);
	cameraComponent.SetTarget(&mainWindow);
	camera->AddComponent<Ndk::NodeComponent>();

	//Cr�ation d'un canvas
	///Permet de disposer diff�rents widgets de fa�on ordonn�e dans la fen�tre
	Ndk::Canvas canvas(world.CreateHandle(), mainWindow.GetEventHandler(), mainWindow.GetCursorController().CreateHandle());
	
	
	//Cr�ation du StateData
	///Contient les �l�ments n�c�ssaires au fonctionnement des states
	NzP::StateData stateData;
	stateData.app = &application;
	stateData.window = &mainWindow;
	stateData.canvas = &canvas;
	stateData.camera = camera;
	stateData.world = world.CreateHandle();

	//Cr�ation et initialisation de la StateMachine
	///On l'initialise avec un MenuState
	Ndk::StateMachine fsm{ std::make_shared<NzP::MenuState>(stateData) };

		while (application.Run())
		{
			if (!fsm.Update(application.GetUpdateTime()))
			{
				// Gestion d'erreur si besoin 
				return EXIT_FAILURE; // EXIT_SUCCESS si c'est juste la fin du jeu 
			}
			mainWindow.Display();
		}
	return EXIT_SUCCESS;
}
