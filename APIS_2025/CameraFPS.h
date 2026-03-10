#pragma once
#include "Camera.h"

class CameraFPS: public Camera
{
public:
	CameraFPS(projectionType_e type, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt);
	void step(double timeStep) override;
};

