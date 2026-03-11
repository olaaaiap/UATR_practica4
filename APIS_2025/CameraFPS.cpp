#include "CameraFPS.h"
#include "GLFWInputManager.h"

CameraFPS::CameraFPS(projectionType_e type, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt)
	:Camera(type, position, up, lookAt)
{
}

void CameraFPS::step(double timeStep)
{
    //actualizar movimientos
    double vel = 0.4; //unidadesGl segundo
    double velRot = 1.0;

    if (GLFWInputManager::keyboardState[GLFW_KEY_D])
    {
        this->posicion.x -= vel * timeStep;
        lookAt.x += vel * timeStep;
    }
    if (GLFWInputManager::keyboardState[GLFW_KEY_A])
    {
        this->posicion.x += vel * timeStep;
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

    direction = glm::vec4(forward, 0.0f);

    //calcular matriz vista
    view = glm::lookAt(glm::vec3(posicion), glm::vec3(lookAt), glm::vec3(0, 1, 0));

}
