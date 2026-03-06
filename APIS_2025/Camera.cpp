#include "Camera.h"

Camera::Camera(projectionType_e type, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt)
	: type(type), up(up), lookAt(lookAt)
{
	posicion = glm::vec4(position, 1.0f);
	computeProjectionMatrix();
	computeViewMatrix();
}

glm::mat4 Camera::getProjection()
{
	return projection;
}

glm::mat4 Camera::getView()
{
	return view;
}

void Camera::computeProjectionMatrix()
{
	if (type == projectionType_e::perspectiva) 
	{
		//calcular matriz proyección
		projection = glm::perspective(glm::radians(fovy), aspectRatio, 0.01, 1000.0);

	}
	else 
	{
		//calcular matriz proyección
		double size = 10.0; //Mitad del alto de la camara
		projection = glm::ortho(-size * aspectRatio, size * aspectRatio, -size, size, 0.01, 1000.0);
	
	}
}

void Camera::computeViewMatrix()
{
	//calcular matriz vista
	view = glm::lookAt(glm::vec3(posicion), glm::vec3(lookAt), glm::vec3(up));
}
