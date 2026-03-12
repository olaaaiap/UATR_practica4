#include "CameraFPS.h"
#include "GLFWInputManager.h"
#include <algorithm>

CameraFPS::CameraFPS(projectionType_e type, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt)
	:Camera(type, position, up, lookAt)
{
}

void CameraFPS::step(double timeStep)
{
    double vel = 0.4;
    double velRot = 1.0;
    const float mouseSens = 0.10f;
    glm::vec3 strafeDir = normalize(glm::cross(glm::vec3(this->up), glm::vec3(direction)));


    if (GLFWInputManager::keyboardState[GLFW_KEY_D])
    {
        this->posicion += glm::vec4(strafeDir, 0.0f) * (float)(vel * timeStep);
    }
    if (GLFWInputManager::keyboardState[GLFW_KEY_A])
    {
        this->posicion -= glm::vec4(strafeDir, 0.0f) * (float)(vel * timeStep);
    }
    if (GLFWInputManager::keyboardState[GLFW_KEY_W])
    {
        this->posicion += glm::vec4(direction, 0.0f) * (float)(vel * timeStep);
    }
    if (GLFWInputManager::keyboardState[GLFW_KEY_S])
    {
        this->posicion -= glm::vec4(direction, 0.0f) * (float)(vel * timeStep);

    }

    static double ultimoPRatonX = GLFWInputManager::mouseState.x;
    static double ultimoPRatonY = GLFWInputManager::mouseState.y;
    const double ratonX = GLFWInputManager::mouseState.x;
    const double ratonY = GLFWInputManager::mouseState.y;

    //Solo mover la camara si se esta clickando el boton izquierdo
    if (GLFWInputManager::mouseState.button[GLFW_MOUSE_BUTTON_LEFT])
    {
        const double dx = ratonX - ultimoPRatonX;
        const double dy = ratonY - ultimoPRatonY;

        ultimoPRatonX = ratonX;
        ultimoPRatonY = ratonY;
        const double sensitivity = 0.10;


        rotacion.y -= dx * sensitivity * velRot;
        rotacion.x -= dy * sensitivity * velRot;

        rotacion.x = std::clamp(rotacion.x, -89.0f, 89.0f); //Para que la camara no se de la vuelta

    }
    else
    {
        ultimoPRatonX = ratonX;
        ultimoPRatonY = ratonY;
    }


    glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotacion.y), glm::vec3(0, 1, 0));
    rotMatrix = glm::rotate(rotMatrix, glm::radians(rotacion.x), glm::vec3(1, 0, 0));
    glm::vec4 lookAtPrime4(lookAtPrime, 0.0f); //lookAtPrime es vec3
    glm::vec3 forward = glm::vec3(rotMatrix * lookAtPrime4);
    forward = glm::normalize(forward);

    lookAt = glm::vec3(posicion) + forward;
    direction = glm::vec4(normalize(glm::vec3(lookAt) - glm::vec3(posicion)), 0);

    //calcular matriz vista
    view = glm::lookAt(glm::vec3(posicion), glm::vec3(lookAt), glm::vec3(0, 1, 0));

}
