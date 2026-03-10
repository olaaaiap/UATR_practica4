#include "Object3D.h"
#include "pugixml.hpp"
#include "GLTexture.h"
#include "Mesh3D.h"
#include "GLSLMaterial.h"

void Object3D::loadDataFromFile(std::string file)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file.c_str());
    if (result) {
        // Cargado correctamente, podemos analizar su contenido ...
        pugi::xml_node buffersNode = doc.child("mesh").child("buffers");

        for (pugi::xml_node bufferNode = buffersNode.child("buffer");
            bufferNode;
            bufferNode = bufferNode.next_sibling("buffer"))
        {
            // Iteramos por todos los buffers
            auto materialNode = bufferNode.child("material");
            auto* material = new GLSLMaterial();

            auto textureNode = materialNode.child("texture");
            if (textureNode)
            {
                //layers
                //añadir nueva textura
                auto* texture = new GLTexture(textureNode.child("layer").text().as_string());
                if (texture) {
                    texture->update();
                    material->setColorText(texture);
                }
            }
            auto shaderNode = materialNode.child("shader");
            if (shaderNode)
            {
                auto shaderList = splitString<std::string>(shaderNode.text().as_string(), ',');
                material->loadPrograms(shaderList);
            }

            //No tenemos shininess por ahora
            ////auto shiniNode = materialNode.child("shininess");
            ////if (shiniNode)
            ////{
            ////    //layers
            ////    //añadir nueva textura
            ////    material->shininess = shiniNode.text().as_int();
            ////}

            std::string meshData = bufferNode.child("meshData").text().as_string();
            loadObj(meshData, material);
        }

    }
    else {
        // No se ha podido cargar
        std::cout << result.description() << std::endl;
    }
}


void Object3D::loadObj(std::string objFile, GLSLMaterial* mat)
{

    std::ifstream f(objFile, std::ios_base::in);
    std::vector<glm::vec4> vPos;
    std::vector<glm::vec2> vTC;
    std::vector<glm::vec4> vNorm;
    std::string line;
    Mesh3D m;
    m.setMaterial(nullptr);
    int vertexOffset = 0;
    bool computeNormals = false;
    while (std::getline(f, line, '\n')) {
        std::istringstream str(line);
        std::string key;
        str >> key;
        if (key[0] != '#') {
            if (key == "o")
            {
                if (m.getMaterial()) {
                    m.setMeshId(meshIdCounter++);
					addMesh(&m);
                }
                m.setMaterial(mat);
                m.clearvVertList();
				m.clearvTriangleIdxList();
                vertexOffset = vPos.size();
            }
            else if (key == "v")
            {
                glm::vec4 v(1.0f);
                str >> v.x >> v.y >> v.z;
                vPos.push_back(v);
                this->vertexList.push_back(vertex_t{});
            }
            else if (key == "vn")
            {
                glm::vec4 v(0);
                str >> v.x >> v.y >> v.z;
                vNorm.push_back(v);
            }

            else if (key == "vt")
            {
                glm::vec2 v(0);
                str >> v.x >> v.y;
                vTC.push_back(v);
            }
            else if (key == "f")
            {
                std::string vert;
                vertex_t v[3];
                int vIndex[3] = { 0 };
                for (int i = 0; i < 3; i++)
                {
                    /*  str >> vert;
                      auto indexes = splitString<int>(vert, '/');
                      v[i] = { vPos[indexes[0] - 1],{0,0,0,0},//vNorm[indexes[2] -m1],
                          vTC[indexes[1] - 1] };
                      this->vertexList[indexes[0] - 1 - vertexOffset] = v[i];
                      this->vertexIndexList.push_back(indexes[0] - 1 - vertexOffset);
                      */
                    str >> vert;
                    auto indexes = splitString<int>(vert, '/');
                    if (indexes.size() == 3) //si hay tres índices por faceta, se carga la información de normales y textura
                    {
                        v[i] = { vPos[indexes[0] - 1],vTC[indexes[1] - 1] };
                    }
                    else if (indexes.size() == 1)//si no, no hay textura y sólo se carga el dato de posición de vértice
                    {
                        v[i] = { vPos[indexes[0] - 1],{0,0} };
                        computeNormals = true; //se deben recalcular las normales al acabar de cargar información
                    }
                    this->vertexList[indexes[0] - 1 - vertexOffset] = v[i];
                    this->vertexIndexList.push_back(indexes[0] - 1 - vertexOffset);

                    m.addVertex(v[i]);
                    m.getTriangleList()->push_back(
                        static_cast<glm::uint32>(m.getVertList()->size() - 1)
                    );
                }
            }
        }
    }
    /*if (computeNormals)
        this->recomputeNormals();*/
    if (m.getMaterial()) {
		m.setMeshId(meshIdCounter++);
		addMesh(&m);
    }
}


//
//void Object3D::recomputeNormals()
//{
//    for (auto& v : this->vertexList) //por cada vértice, resetear sus normales
//        v.vNormal = { 0,0,0,0 };
//    for (auto it = this->vertexIndexList.begin(); it != vertexIndexList.end();)//recorrer la lista de índices de vértices
//    {
//        vertex_t& v1 = this->vertexList[*it]; it++; //cada tres vértices, una faceta
//        vertex_t& v2 = this->vertexList[*it]; it++;
//        vertex_t& v3 = this->vertexList[*it]; it++;
//        glm::vec3 l1 = glm::normalize(v2.vPosition - v1.vPosition); //obtener dos aristas
//        glm::vec3 l2 = glm::normalize(v2.vPosition - v3.vPosition);
//        glm::vec3 norm = glm::normalize(glm::cross(l2, l1)); //obtener la normal
//        v1.vNormal = glm::normalize(v1.vNormal + glm::vec4(norm, 0.0f)); //acumular la normal, en caso de ser vértices compartidos
//        v2.vNormal = glm::normalize(v2.vNormal + glm::vec4(norm, 0.0f));
//        v3.vNormal = glm::normalize(v3.vNormal + glm::vec4(norm, 0.0f));
//    }
//
//}

