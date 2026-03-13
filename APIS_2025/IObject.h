#pragma once
#include "IEntity.h"
#include "Mesh3D.h"
#include <vector>

class IObject : public IEntity
{
protected:
	//Mesh3D* mesh; //Puntero de la malla que almacenará la geometría de este objeto.
	std::vector<Mesh3D*> meshes; //Nueva lista de mallas
public:
	static inline int meshIdCounter = 0;

	static inline int objectCounter = 0;
	int objectId;
	int tipo;



	/*std::vector<vertex_t> vertexList;
	std::vector<int> vertexIndexList;*/

	Mesh3D* GetMesh(int pos);
	std::vector<Mesh3D*>& getMeshes();
	//void SetMesh(Mesh3D* m);
	void addMesh(Mesh3D* m);
	
	//mesh = m;
	

	virtual void loadDataFromFile(std::string file) = 0;
};

