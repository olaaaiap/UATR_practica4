#pragma once
#include "mapi/common.h"

typedef enum class programTypes_e {
	vertex = 0, 
	fragment = 1
}programTypes_e;


class IProgram
{
public:
	programTypes_e type; //Tipo de programa cargado
	std::string fileName; //Nombre del archivo cargado
	unsigned int idProgram; //Identificador único de programa.

	IProgram(std::string fileName); //Constructor. Inicializa la variable de nombre.
	IProgram() {};

	virtual void readFile() = 0; //Método virtual puro de carga de código de ficheros.

	virtual void compile() = 0; // Método virtual puro que representa la ejecución de compilación de programa

	virtual void checkErrors() = 0; //Método que imprimirá por pantalla cualquier error encontrado durante la compilación o carga del archivo

};

