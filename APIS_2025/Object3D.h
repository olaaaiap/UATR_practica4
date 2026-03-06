#pragma once
#include "IObject.h"

class GLSLMaterial;

class Object3D: public IObject
{
public:

    void loadDataFromFile(std::string file) override;
    void loadObj(std::string objFile, GLSLMaterial* mat);
};

