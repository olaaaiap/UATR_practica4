#pragma once
#include "mapi/common.h"
#include "Object3D.h"
#include "IRender.h"


typedef struct
{
	//id de array de buffers
	unsigned int arrayBufferId;
	//id de vertex array buffer
	unsigned int vertexArrayId;
	//id de vertex index buffer
	unsigned int vertexIdxArrayId;
}bo_t; //datos de buffer object

class GL1Render : public IRender
{
	GLFWwindow* window; //Puntero a una ventana GLFW.
	
	//Variables para la funcion draw de GL1Render
	std::vector<Object3D*> objectList;
	std::map<int, bo_t>  bufferObjectList; 


public:
    GL1Render(double width, double height);
	void init();
	void setupObject(Object3D* obj);
	void removeObject(Object3D* obj);
	void drawObjects(std::list<Object3D*>* objs);
	bool isClosed() override;

	GLFWwindow* getWindow() const { return window; }
};

