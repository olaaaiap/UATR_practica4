#include "GLSLMaterial.h"


void GLSLMaterial::addTriangle(glm::uint32 vldx1, glm::uint32 vldx2, glm::uint32 vldx3)
{
    if (vTriangleIdxlist == nullptr)
        vTriangleIdxlist = new std::vector<glm::uint32>();
    vTriangleIdxlist->push_back(vldx1);
    vTriangleIdxlist->push_back(vldx2);
	vTriangleIdxlist->push_back(vldx3);
}

void GLSLMaterial::loadPrograms(const std::vector<std::string>& files)
{
    if (!program) {
        program = new GLSLProgram();
    }

    for (auto& f : files)
        program->addProgram(f);

    program->linkProgram();
}

void GLSLMaterial::prepare()
{
    program->use();

	World* world = System::GetWorld();
	if (!world) return;
    int activeCameraIndex = world->getActiveCamera();
	Camera* cam = world->getCamera(activeCameraIndex);

    //Inicializar a matriz de identidad
    glm::mat4 view(1.0f);
    glm::mat4 proj(1.0f);
    if (cam) {
        view = cam->getView();
        proj = cam->getProjection();
    }

	glm::mat4 model = System::GetModelMatrix();
    glm::mat4 mvp = proj * view * model;
	program->setMatrix("mMat", mvp);
    program->setMatrix("M", model);
    

    if (colorText != nullptr) {
        program->setColorTextEnable();
        program->bindColorTextureSampler(0, colorText);
    }
    else {
        program->setColorTextDisable();
    } 


    program->setVertexAttrib("vTexCoord", sizeof(vertex_t), (void*)offsetof(vertex_t, vTextCoords), 2, GL_FLOAT);
     

    glm::vec4 matColor(1.0f); // fallback blanco
    matColor = this->getColorRGBA();
    program->setVec4("colorRGBA", matColor);




}
