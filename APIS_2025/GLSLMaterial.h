#pragma once
#include "Material.h"
#include "GLSLProgram.h"
#include "System.h"

class GLSLMaterial : public Material
{
	Material* mat;
	std::vector<glm::uint32>* vTriangleIdxlist; //lista de indentificadores de vértices. Cada triplete de ids serán un triangulo.

public:

	Material* getMaterial() { return mat; }
	void setMaterial(Material* material) { mat = material; }
	std::vector<glm::uint32>* getvTriangleIdxList(std::vector<glm::uint32>** idxList) { return vTriangleIdxlist;}
	void setvTriangleIdxList(std::vector<glm::uint32>* idxList) { vTriangleIdxlist = idxList; }

	void addTriangle(glm::uint32 vldx1, glm::uint32 vldx2, glm::uint32 vldx3);
    //void SetModelMatrix(const glm::mat4& modelMatrix);
    void loadPrograms(const std::vector<std::string>& files) override;
    void prepare() override;
};
