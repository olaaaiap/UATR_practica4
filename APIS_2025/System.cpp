#include "System.h"
#include "FactoryEngine.h"

void System::SetRender(IRender* r)
{
	render = r;
}

IRender* System::GetRender()
{
	return render;
}

void System::SetInputManager(InputManager* im)
{
	inputManager = im;
}

InputManager* System::GetInputManager()
{
	return inputManager;
}

World* System::GetWorld()
{
	return world;
}

void System::SetWorld(World* w)
{
	world = w;
}


glm::mat4 System::GetModelMatrix()
{
	return ModelMatrix;
}

void System::SetModelMatrix(const glm::mat4& matrix)
{
	ModelMatrix = matrix;
}

void System::initSystem()
{
	//Inicializar el sistema
	//Inicializar atributos de esta clase
	world = new World();
	render = FactoryEngine::getNewRender();
	inputManager = FactoryEngine::getNewInputManager();
	render->init();
	inputManager->init(glfwGetCurrentContext());
	
}

void System::addObject(Object3D* obj) 
{
	world->addObject(obj);
}

void System::exit() 
{
	end = true;
}

void System::mainLoop()
{
	//Llamar a la funcion setupObject de render con cada objeto del mundo que esté activo
	for (auto obj : world->getObjects()) 
	{
		render->setupObject(obj);
	}

	float newTime = static_cast<float>(glfwGetTime());
	float deltaTime = 0;
	float lastTime = newTime;

	while (!end)
	{
		//Calcular deltaTime
		newTime = static_cast<float>(glfwGetTime());
		deltaTime = newTime - lastTime;
		lastTime = newTime;

		//Actualizar el mundo y sus objetos (llamar al metodo update del mundo activo)
		world->update(deltaTime);

		//dibujar objetos
		render->drawObjects(&world->getObjects());
	}
}