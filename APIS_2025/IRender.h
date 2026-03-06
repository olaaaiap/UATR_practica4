#pragma once
#include "Object3D.h"
#include <vector>




class IRender
{
	int width;  //Ancho del framebuffer
	int height; //Alto del framebuffer
public:

	int GetWidth() const;
	int GetHeight() const;

	void SetWidth(int width);
	void SetHeight(int height);


	virtual void init() = 0; //Método que inicializa las librerías que se utilizarán para implementar el render.
	virtual void setupObject(Object3D* obj) = 0; //Método que prepara las estructuras internas para dibujar un objeto.
	virtual void removeObject(Object3D* obj) = 0; //Método análogo a setupObject, para liberar las estructuras internas.
	virtual void drawObjects(std::list<Object3D*>* objs) = 0; //Método que dibuja una lista de objetos pasada por parámetros.
	virtual bool isClosed() = 0; //Para averiguar si se ha cerrado la "sesión" del render. En nuestro caso, si se ha cerrado la ventana.
};

