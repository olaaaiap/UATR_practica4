#pragma once
#include "IEntity.h"


typedef enum class projectionType_e {
	ortogonal = 0,
	perspectiva = 1
}projectionType_e;


class Camera: public IEntity
{
protected:
	glm::mat4 view;
	glm::mat4 projection;
	glm::vec3 up;
	glm::vec3 lookAt;
	projectionType_e type; //enumerador para elegir entre cámaras de tipo ortogonal o perspectiva
	double fovy = 45; //angulo de apertura en grados
	double aspectRatio = 4.0 / 3.0; //4:3

public:
	Camera(projectionType_e type, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt);
	glm::mat4 getProjection();
	glm::mat4 getView();
	void computeProjectionMatrix();
	void computeViewMatrix();

	virtual void step(double timestep) = 0;
};

