#include "IObject.h"

Mesh3D* IObject::GetMesh(int pos)
{
	return this->meshes[pos];
}

std::vector<Mesh3D*>& IObject::getMeshes()
{
	return this->meshes;
}

void IObject::addMesh(Mesh3D* m)
{
	this->meshes.push_back(m);
}

//void IObject::SetMesh(Mesh3D* m)
//{
//	this->mesh = m;
//}
