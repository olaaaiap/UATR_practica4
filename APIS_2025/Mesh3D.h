#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "vertex_t.h"

// Forward declaration para evitar ciclos
class Material;
/*
typedef struct
{
    glm::vec4 pos;
} vertex_t;
*/
class Mesh3D
{
protected:
    std::vector<vertex_t> vVertList;
    std::vector<glm::uint32> vTriangleIdxList;
    Material* mat = nullptr;

public:
    static inline int meshCounter = 0;
    int meshId;

	Material* getMaterial() { return mat; }

	void setMaterial(Material* m) { mat = m; }


    Mesh3D(); // Constructor por defecto

    int getMeshID(); // Devuelve el ID único de esta malla

    void addVertex(vertex_t vertex);

    std::vector<vertex_t>* getVertList(); // Método para acceder a la lista de vértices

    std::vector<glm::uint32>* getTriangleList() { return &vTriangleIdxList; }
};
