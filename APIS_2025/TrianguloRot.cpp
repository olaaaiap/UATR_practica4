#include "TrianguloRot.h"
#include "GLFWInputManager.h"
#include "Mesh3D.h"
#include "FactoryEngine.h"


TrianguloRot::TrianguloRot()
{
    Mesh3D* mesh = new Mesh3D();
    this->addMesh(mesh);
    this->objectId = objectCounter++;



    mesh->setVertList({
    { {  0.0f,  0.5f, 0.0f, 1.0f },{ 0.0f, 0.0f }}, // superior
    { { -0.5f, -0.5f, 0.0f, 1.0f }, { 0.0f, 0.0f } }, // abajo izquierda
    { {  0.5f, -0.5f, 0.0f, 1.0f }, { 0.0f, 0.0f } }  // abajo derecha
        });


    //Triángulo 3 índices
    mesh->setTriangleIdxList({ 0, 1, 2 });

    FactoryEngine factoryEngine;
    Material* mat = factoryEngine.getNewMaterial();
    if (mat) {
        mat->loadPrograms({ "data/shader.vert", "data/shader.frag" });
	    mesh->setMaterial(mat);
    }

    this->setPosicion({ 0.0f, 0.0f, 0.0f, 1.0f });
    this->setRotacion({ 0.0f, 0.0f, 0.0f, 1.0f });
    this->setEscala({ 1.0f, 1.0f, 1.0f, 1.0f });
}

void TrianguloRot::step(double deltaTime)
{
    float velRot = 90.0f;
    glm::vec4 rot = this->GetRotacion();

    if (GLFWInputManager::keyboardState[GLFW_KEY_R])
        rot.y += static_cast<float>(velRot * deltaTime);

    if (GLFWInputManager::keyboardState[GLFW_KEY_T])
        rot.y -= static_cast<float>(velRot * deltaTime);

    this->setRotacion(rot);

    if (GLFWInputManager::keyboardState[GLFW_KEY_E])
        std::exit(0);
}
