#pragma once
#include <map>
//#include <glad/glad.h>
#include "GL1Render.h"
#include "Material.h"
#include "Mesh3D.h"

typedef struct boIDS_t 
{
    unsigned int id;
    unsigned int vbo;
    unsigned int idxbo;
} boIDS_t;

class GL4Render : public GL1Render 
{
    //std::map<int, boIDS_t> bufferObjects;
    std::map<int, std::vector<boIDS_t>> bufferObjects;

public:

    GL4Render(double w, double h);

    virtual void setupObject(Object3D* obj) override;
    virtual void removeObject(Object3D* obj) override;
    virtual void drawObjects(std::list<Object3D*>* objs) override;
	virtual void init() override;
    virtual void drawObject(Object3D* obj, Mesh3D* mesh);

};
