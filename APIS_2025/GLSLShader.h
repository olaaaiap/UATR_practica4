#pragma once
#include "mapi/common.h"
#include "IProgram.h"


class GLSLShader : public IProgram
{
	std::string code; //Codigo fuente del shader
public:
	bool compiled = false;
	GLSLShader(std::string fileName, programTypes_e type);
	void readFile() override;
	void compile() override;
	void checkErrors() override;
};

