#pragma once
#include "Object3D.h"

class AsianTown : public Object3D
{
public:
	AsianTown(const std::string& mshFile);

	void step(double deltaTime) override;
};

