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
	void setMeshId(int id) { meshId = id; }
	void clearvVertList() { vVertList.clear(); }
	void clearvTriangleIdxList() { vTriangleIdxList.clear(); }

    Mesh3D(); // Constructor por defecto

    int getMeshID(); // Devuelve el ID único de esta malla

    void addVertex(const vertex_t& vertex);

    std::vector<vertex_t>* getVertList(); // Método para acceder a la lista de vértices

    std::vector<glm::uint32>* getTriangleList() { return &vTriangleIdxList; }

    void addTriangleIdxList(glm::uint32 idx) { vTriangleIdxList.push_back(idx); }
};
