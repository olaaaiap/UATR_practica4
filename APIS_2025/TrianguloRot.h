#pragma once
#include "Object3D.h"
#include <glm/glm.hpp>


class TrianguloRot : public Object3D
{
public:
    TrianguloRot();

    void step(double deltaTime) override;
};

