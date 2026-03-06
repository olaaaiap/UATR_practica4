#include "GL1Render.h"

GL1Render::GL1Render(double width, double height)
{
	this->SetWidth(static_cast<int>(width));
	this->SetHeight(static_cast<int>(height));
}

void GL1Render::init()
{
	//Inicialización de GLFW
	if (glfwInit() != GLFW_TRUE) {
		std::cout << "ERROR iniciando glfw\n";
	}
	else {
		//iniciar opengl
		#ifdef __APPLE__
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		#endif


		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		// Use configured width/height
		this->window = glfwCreateWindow(this->GetWidth(), this->GetHeight(), "Practica 2 APIS3D", nullptr, nullptr); //nullptr->para que coja los valores por defecto
		
		glfwMakeContextCurrent(this->window);

		gladLoadGL(glfwGetProcAddress); // cargar funciones OpenGL

		// Setup basic GL state
		glViewport(0, 0, this->GetWidth(), this->GetHeight());
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// Use an orthographic projection so coordinates in [-1,1] are visible
		glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
	}

}

void GL1Render::setupObject(Object3D* obj)
{
    bo_t bo = { 0,0,0 };

	//crear buffers objects
	glGenVertexArrays(1, &bo.arrayBufferId);
	glGenBuffers(1, &bo.vertexArrayId);
	glGenBuffers(1, &bo.vertexIdxArrayId);
	//copiar datos a GPU
	glBindVertexArray(bo.arrayBufferId); //activar lista de arrays
	glBindBuffer(GL_ARRAY_BUFFER, bo.vertexArrayId);//activar lista de vértices
	int numElements = obj->vertexList.size();
	glBufferData(GL_ARRAY_BUFFER, numElements * sizeof(vertex_t), obj->vertexList.data(), GL_STATIC_DRAW); //copiar vertices

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.vertexIdxArrayId);//activar lista de indices de vértices
	numElements = obj->vertexIndexList.size();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElements * sizeof(unsigned int), obj->vertexIndexList.data(), GL_STATIC_DRAW); //copiar indices de vertices
	//guardar ids de buffers
	bufferObjectList[obj->objectId] = bo;
}

void GL1Render::removeObject(Object3D* obj)
{
	//Metodo para borrar un objeto. Se busca en la lista a través de su referencia/puntero y se borra
	auto it = bufferObjectList.find(obj->objectId);
	if (it != bufferObjectList.end()) {
		bo_t bo = it->second;
		glDeleteBuffers(1, &bo.vertexArrayId);
		glDeleteBuffers(1, &bo.vertexIdxArrayId);
		glDeleteVertexArrays(1, &bo.arrayBufferId);
		bufferObjectList.erase(it);
	}
}


bool GL1Render::isClosed() {
    if (!this->window) return true;
    return glfwWindowShouldClose(window);
}



void GL1Render::drawObjects(std::list<Object3D*>* objs)
{
    // Clear before drawing
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Ensure we are using modelview matrix
    glMatrixMode(GL_MODELVIEW);

    // Recorrer todos los objetos
    for (auto& obj : *objs)
    {
        // Calcular matriz modelo
        auto model = obj->computeModelMatrix();

        // Guardar la matriz actual en la pila
        glPushMatrix();
        glLoadIdentity(); // Cargar matriz identidad
        glMultMatrixf(&model[0][0]); // Multiplicar por la matriz modelo del objeto

        // Activar buffers de datos
        auto bo = bufferObjectList[obj->objectId];
        glBindVertexArray(bo.arrayBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, bo.vertexArrayId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.vertexIdxArrayId);

        // Describir los buffers
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(4, GL_FLOAT, sizeof(vertex_t), (void*)offsetof(vertex_t, vPosition));
        

		//glEnableClientState(GL_COLOR_ARRAY);//voy a describir listas de color de vértice
		//glColorPointer(4, GL_FLOAT, sizeof(vertex_t), (void*)offsetof(vertex_t, vColor)); //4 floats después de 4 floats (posición)


        // Dibujar los elementos
		glDrawElements(GL_TRIANGLES, obj->vertexIndexList.size(), GL_UNSIGNED_INT, nullptr);

        // Restaurar la matriz anterior
        glPopMatrix();

        // Deshabilitar los estados de cliente
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
    }

    // Present frame and process events
    if (this->window) {
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}

