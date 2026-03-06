#pragma once
#include <list>
#include "Object3D.h"
#include "Camera.h"

class World
{
	//Clase que estará encargada de contener un escenario con objetos, cámaras...
	std::list<Object3D*> objects; //Lista de objetos que están en el escenario.
	std::list<Camera*> cameras; //Lista de camaras que están en el escenario.
	int activeCamera = 0; //Indice de la camara activa
public:
	World();
	void addObject(Object3D* obj); //Método para añadir objetos a la lista de objetos de este mundo.
	void removeObject(Object3D* obj); //Método para borrar un objeto.
	void addCamera(Camera* cam); //Método para añadir cámaras a la lista de objetos de este mundo.
	void removeCamera(Camera* cam); //Método para borrar una cámara.
	size_t getNumObjects(); //Método que devuelve el tamaño de la lista de objetos.
	Object3D* getObject(size_t index); //Método que devuelve el objeto que se encuentra en la posición index de la lista.
	Camera* getCamera(size_t index); //Método que devuelve la cámara que se encuentra en la posición index de la lista.
	int getActiveCamera(); //Getter para obtener el índice de la cámara activa. devuelve 0 si activeCamera tiene un valor fuera de los rangos.
	void setActiveCamera(int activeCameraI);
	std::list<Object3D*>& getObjects(); //Método que devuelve por referencia la lista completa de objetos.
	void update(float deltaTime); //Método que actualiza el estado de este mundo. Llama al método step de cada uno de sus objetos pasándoles la variable deltaTime.
};

