#include "IProgram.h"

IProgram::IProgram(std::string fileName)
{
	this->idProgram = -1;
	this->fileName = fileName;
	this->type = programTypes_e::vertex;
}
