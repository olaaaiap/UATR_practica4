#include "TrianguloRot.h"
#include "GLFWInputManager.h"
#include "Mesh3D.h"
#include "FactoryEngine.h"


TrianguloRot::TrianguloRot()
{
    // Crear la Mesh3D asociada a este objeto
    Mesh3D* mesh = new Mesh3D();
    this->addMesh(mesh);

    // Asignar ID único del objeto (manteniendo tu sistema actual)
    this->objectId = objectCounter++;

    // Lista de vértices del triángulo
    // Formato: pos (vec4)
    this->vertexList = {
        {{ 0.0f,  0.5f, 0.0f, 1.0f }}, // superior
        {{-0.5f, -0.5f, 0.0f, 1.0f }}, // abajo izquierda
        {{ 0.5f, -0.5f, 0.0f, 1.0f }}  // abajo derecha
    };

    // Triángulo 3 índices
    this->vertexIndexList = { 0, 1, 2 };

    // Rellenar la Mesh3D usando los vértices definidos arriba
    // (mantiene compatibilidad con tu pipeline actual)
    for (auto v : this->vertexList) 
    {
        mesh->addVertex(v);
    }

    //crear programa de dibujado
    FactoryEngine factoryEngine;
    Material* mat = factoryEngine.getNewMaterial();
    if (mat) {
        mat->loadPrograms({ "data/shader.vert", "data/shader.frag" });
	    mesh->setMaterial(mat);
    }

    // Transformaciones iniciales
    this->setPosicion({ 0.0f, 0.0f, 0.0f, 1.0f });
    this->setRotacion({ 0.0f, 0.0f, 0.0f, 1.0f });
    this->setEscala({ 1.0f, 1.0f, 1.0f, 1.0f });
}

// step(deltaTime)
// Rota el triángulo sobre el eje Y
// Teclas R y T controlan la rotación
// Tecla E sale del programa

void TrianguloRot::step(double deltaTime)
{
    float velRot = 90.0f; // grados por segundo

    // Obtener rotación actual
    glm::vec4 rot = this->GetRotacion();

    // Rotación con teclado
    if (GLFWInputManager::keyboardState[GLFW_KEY_R])
        rot.y += static_cast<float>(velRot * deltaTime);

    if (GLFWInputManager::keyboardState[GLFW_KEY_T])
        rot.y -= static_cast<float>(velRot * deltaTime);

    // Aplicar nueva rotación
    this->setRotacion(rot);

    // Salida del programa al pulsar E
    if (GLFWInputManager::keyboardState[GLFW_KEY_E])
        std::exit(0);
}
