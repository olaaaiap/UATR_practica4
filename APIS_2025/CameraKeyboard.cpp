#include "CameraKeyboard.h"
#include "GLFWInputManager.h"

CameraKeyboard::CameraKeyboard(projectionType_e type, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt)
	:Camera(type, position, up, lookAt)
{
}



void CameraKeyboard::step(double timeStep)
{
    //actualizar movimientos
    double vel = 1.0; //unidadesGl segundo
    double velRot = 40.0;

    if (GLFWInputManager::keyboardState[GLFW_KEY_D])
    {
        this->posicion.x += vel * timeStep;
        lookAt.x += vel * timeStep;
    }
    if (GLFWInputManager::keyboardState[GLFW_KEY_A])
    {
        this->posicion.x -= vel * timeStep;
        lookAt.x -= vel * timeStep;
    }
    if (GLFWInputManager::keyboardState[GLFW_KEY_W])
    {
        this->posicion.z += vel * timeStep;
        lookAt.z += vel * timeStep;
    }
    if (GLFWInputManager::keyboardState[GLFW_KEY_S])
    {
        this->posicion.z -= vel * timeStep;
        lookAt.z -= vel * timeStep;

    }

    //Subir/bajar cámara para ver que se están aplicando las texturas correctamente
    if (GLFWInputManager::keyboardState[GLFW_KEY_R])
    {
        this->posicion.y += vel * timeStep;
        lookAt.y += vel * timeStep;
    }
    if (GLFWInputManager::keyboardState[GLFW_KEY_T])
    {
        this->posicion.y -= vel * timeStep;
        lookAt.y -= vel * timeStep;
    }

    //calcular matriz vista

    view = glm::lookAt(glm::vec3(posicion), glm::vec3(lookAt), glm::vec3(0, 1, 0));

}
