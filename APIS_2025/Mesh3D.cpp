#include "Mesh3D.h"
#include "Material.h"

Mesh3D::Mesh3D() {
    meshCounter++;
    meshId = meshCounter;
}

int Mesh3D::getMeshID() {
    return meshId;
}

void Mesh3D::addVertex(vertex_t vertex) {
    vVertList.push_back(vertex);
}

std::vector<vertex_t>* Mesh3D::getVertList() {
    return &vVertList;
}