#include "AsianTown.h"
#include "GLFWInputManager.h"

AsianTown::AsianTown(const std::string& mshFile)
{
	// Transformaciones iniciales
	this->setPosicion({ 0.0f, 0.0f, 0.0f, 1.0f });
	this->setRotacion({ 0.0f, 0.0f, 0.0f, 0.0f });
	this->setEscala({ 1.0f, 1.0f, 1.0f, 1.0f });

	loadDataFromFile(mshFile);
	// Validación: asegurarse de que las mallas tienen datos para VBO/IBO
	auto& meshes = getMeshes();
	if (meshes.empty()) {
		std::cout << "ERROR: AsianTown sin mallas tras cargar: " << mshFile << "\n";
	}
	else {
		for (size_t i = 0; i < meshes.size(); ++i) {
			Mesh3D* m = meshes[i];
			if (!m) {
				std::cout << "ERROR: Mesh3D nula en índice " << i << "\n";
				continue;
			}

			const size_t vCount = m->getVertList() ? m->getVertList()->size() : 0;
			const size_t iCount = m->getTriangleList() ? m->getTriangleList()->size() : 0;

			if (vCount == 0 || iCount == 0) {
				std::cout << "ERROR: Mesh3D[" << i << "] sin geometría. Vertices="
					<< vCount << " Indices=" << iCount << "\n";
			}
		}
	}
	computeModelMatrix();
}


void AsianTown::step(double deltaTime)
{
	// Salida del programa al pulsar E
	if (GLFWInputManager::keyboardState[GLFW_KEY_E])
			std::exit(0);
	computeModelMatrix();
	
}
