#pragma once
#include "IObject.h"
class Object3D: public IObject
{
public:
    void loadDataFromFile(std::string file) override;
};

