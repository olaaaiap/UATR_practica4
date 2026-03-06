#pragma once
#include "IRender.h"
#include "InputManager.h"
#include "World.h"


class System
{
	static inline IRender* render; //Puntero a una clase IRender que implemente esa interfaz.
	static inline InputManager* inputManager; //Puntero a una clase InputManager que la implemente.
	static inline bool end = false; //Variable para indicar si se debe acabar la ejecución.
	static inline World* world; //Variable que apunta a un objeto de tipo "mundo" que representa el escenario activo en este momento.
	static inline glm::mat4 ModelMatrix; //Contiene la mariz modelo del objeto que se está renderizando actualmente.
public:

	//getters y setters
	static void SetRender(IRender* r);
	static IRender* GetRender();

	static void SetInputManager(InputManager* im);
	static InputManager* GetInputManager();

	static World* GetWorld();
	static void SetWorld(World* w);


	static glm::mat4 GetModelMatrix();
	static void SetModelMatrix(const glm::mat4& matrix);


	static void initSystem(); //Inicializa el sistema.
	static void addObject(Object3D* obj); //Añadirá un nuevo objeto a la lista "objects"
	static void exit(); //Método para acabar la ejecución del sistema.
	void mainLoop();
};

