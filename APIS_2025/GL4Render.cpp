#include "GL4Render.h"
#include <GLFW/glfw3.h>
#include "System.h"

GL4Render::GL4Render(double w, double h): GL1Render(w, h){
  
}

void GL4Render::init()
{
    // Llamar a la inicialización base (crea ventana y contexto)
    GL1Render::init();

    // Ahora el contexto está creado y podemos usar llamadas OpenGL
    glEnable(GL_DEPTH_TEST);
}

void GL4Render::setupObject(Object3D* obj)
{
	if (!obj) return;
    
    std::vector<boIDS_t> meshBuffers;

    auto meshes = obj->getMeshes(); //lista de mallas

    for (auto mesh : meshes)
    {

        boIDS_t bo = { 0,0,0 };

        //crear buffers objects
        glGenVertexArrays(1, &bo.id);
        glGenBuffers(1, &bo.vbo);
        glGenBuffers(1, &bo.idxbo);

        //copiar datos a GPU
        glBindVertexArray(bo.id); //activar lista de arrays
        glBindBuffer(GL_ARRAY_BUFFER, bo.vbo);//activar lista de vértices
        int numElements = mesh->getVertList()->size();
        glBufferData(GL_ARRAY_BUFFER, numElements * sizeof(vertex_t), mesh->getVertList()->data(), GL_STATIC_DRAW); //copiar vertices

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idxbo);//activar lista de indices de vértices
        int numIndices = mesh->getTriangleList()->size();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(glm::uint32), mesh->getTriangleList()->data(), GL_STATIC_DRAW); //copiar indices de vertices

        mesh->getMaterial()->getProgram()->use();
        mesh->getMaterial()->getProgram()->setVertexAttrib("vPos", sizeof(vertex_t), (void*)offsetof(vertex_t, vPosition), 4, GL_FLOAT);
        
        meshBuffers.push_back(bo);

    }
    //guardar ids de buffers
    bufferObjects[obj->objectId] = meshBuffers;
}

void GL4Render::removeObject(Object3D* obj)
{
    auto it = bufferObjects.find(obj->objectId);
    if (it != bufferObjects.end()) {
        auto& bos = it->second;

        // Borrar cada VAO/VBO/IBO
        for (auto& bo : bos)
        {
            glDeleteBuffers(1, &bo.vbo);
            glDeleteBuffers(1, &bo.idxbo);
            glDeleteVertexArrays(1, &bo.id);
        }
        bufferObjects.erase(it);
    }
}

void GL4Render::drawObjects(std::list<Object3D*>* objs)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);

    for (auto& obj : *objs) 
    {
        // Calcular matriz modelo
        auto model = obj->computeModelMatrix();

        // Establecer la matriz modelo en el System para que GLSLMaterial::prepare() la use
        System::SetModelMatrix(model);

        // Guardar la matriz actual en la pila
        glPushMatrix();
        glLoadIdentity(); // Cargar matriz identidad
        glMultMatrixf(&model[0][0]); // Multiplicar por la matriz modelo del objeto

        // Preparar el material (usa el programa y sube MVP desde la cámara activa)
        auto meshes = obj->getMeshes();

        for (auto& mesh : meshes)
        {
            if (!mesh || !mesh->getMaterial()) continue;

            // Activar shader y subir matrices
            mesh->getMaterial()->prepare();

            // Dibujar esa malla
            drawObject(obj, mesh);
        }

      
        glPopMatrix();
    }

    if (this->getWindow()) {
        glfwSwapBuffers(this->getWindow());
        glfwPollEvents();
    }
}

void GL4Render::drawObject(Object3D* obj, Mesh3D* mesh)
{
    auto& bos = bufferObjects[obj->objectId];
    auto meshes = obj->getMeshes();
    size_t meshIndex = 0;

    for (size_t i = 0; i < meshes.size(); ++i)
    {
        if (meshes[i] == mesh)
        {
            meshIndex = i;
            break;
        }
    }

    //obtener buffer correspondiente a esta malla
    auto& bo = bos[meshIndex];


    glBindVertexArray(bo.id);
    glBindBuffer(GL_ARRAY_BUFFER, bo.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.idxbo);

    // Describir los buffers
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(4, GL_FLOAT, sizeof(vertex_t), (void*)offsetof(vertex_t, vPosition));
    // Dibujar los elementos
    glDrawElements(GL_TRIANGLES, mesh->getTriangleList()->size(), GL_UNSIGNED_INT, nullptr);

    // Deshabilitar los estados de cliente
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

}
