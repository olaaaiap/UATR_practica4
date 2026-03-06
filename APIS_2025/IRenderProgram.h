#pragma once
#include "mapi/common.h"
#include "IProgram.h"
#include "ITexture.h"

class IRenderProgram
{

public:
	std::vector<IProgram*> shaders; // Vector con los programas cargados para el dibujado(shaders de vértices y fragmentos en nuestro caso)
	std::map<std::string, unsigned int> varList; //Mapa con la lista de variables activas encontrada en los programas cargados anteriormente
	
	virtual void addProgram(std::string fileName)=0; // Añade un programa identificado por su nombre de archivo para compilarlo
	virtual void linkProgram()=0; // Una vez añadidos todos los programas,compila y linka para generar el programa final
	virtual void use()=0; // Activa el uso de este programa
	virtual void checkLinkerErrors()=0; // Muestra por terminal los errores encontrados durante la compilación y linkado

	virtual unsigned int getVarLocation(const std::string& name) = 0;

	virtual void setVertexAttrib(std::string name, GLsizei stride, void* offset, GLint count, GLenum type) = 0;
	virtual void setInt(std::string name, int val) = 0;
	virtual void setFloat(std::string name, float val) = 0;
	virtual void setVec3(std::string name, const glm::vec3& vec) = 0;
	virtual void setVec4(std::string name, const glm::vec4& vec) = 0;
	virtual void setMatrix(std::string name, const glm::mat4& matrix) = 0;
	virtual void setColorTextEnable() = 0; //Inicializa la variable uniform que indicará al shader de fragmentos si debe de utilizar texturas al colorear
	virtual void setColorTextDisable() = 0;
	virtual void bindColorTextureSampler(int binding, ITexture* text) = 0; // Selecciona el punto de enlace (binding)para la textura pasada por parámetros
};

