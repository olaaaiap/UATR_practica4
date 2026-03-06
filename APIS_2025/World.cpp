#include "World.h"
#include "System.h"

World::World()
{
}


void World::addObject(Object3D* obj)
{
	this->objects.push_back(obj);
}

void World::removeObject(Object3D* obj)
{
	this->objects.remove(obj);
}

void World::addCamera(Camera* cam)
{
	this->cameras.push_back(cam);
}

void World::removeCamera(Camera* cam)
{
	this->cameras.remove(cam);
}

size_t World::getNumObjects()
{
	return this->objects.size();
}

Object3D* World::getObject(size_t index)
{
	if (index >= this->objects.size()) return nullptr;

	std::list<Object3D*>::iterator iterador = objects.begin();
	std::advance(iterador, index);
	return *iterador;
}

Camera* World::getCamera(size_t index)
{
	if (index >= this->cameras.size()) return nullptr;

	std::list<Camera*>::iterator iterador = cameras.begin();
	std::advance(iterador, index);
	return *iterador;
}

int World::getActiveCamera()
{
	if (activeCamera<0 || activeCamera >= cameras.size()) {
		activeCamera = 0;
	}
	return activeCamera;
}

void World::setActiveCamera(int activeCameraI)
{
	if (activeCameraI < 0 || activeCameraI >= cameras.size()) {
		activeCameraI = 0;
	}
	activeCamera = activeCameraI;
}

std::list<Object3D*>& World::getObjects()
{
	return this->objects;
}

void World::update(float deltaTime)
{
	for (auto obj : this->objects) 
	{
		obj->step(deltaTime);
	}
	for (auto cam : this->cameras)
	{
		cam->step(deltaTime);
	}
}

