#pragma once
#include "ITexture.h"

class GLTexture: public ITexture
{
    GLuint GlTextID;
public:
    GLTexture() : ITexture() {};
    GLTexture(std::string fileName) : ITexture(fileName) { };
    void update() override;

	GLuint getGlTextId() { return GlTextID; };
	void setGlTextId(GLuint id) { GlTextID = id; };
};

