#pragma once
#include "IRenderProgram.h"


class GLSLProgram: public IRenderProgram
{
	unsigned int programId; //identificador OpenGl de programa GLSL


public:
	bool linked = false;
	void readVarList(); //Método para interrogar a un shader y averiguar todas las variables de tipo uniform y attribute que pueden ser accedidas, y guardarlas en el mapa “varList” :
	unsigned int getVarLocation(const std::string& name) override;//Método para obtener el “Location” de una variable de GLSL, y que además  muestra un error si no se ha encontrado
	void addProgram(std::string fileName)  override; // Añade un programa identificado por su nombre de archivo para compilarlo
	void linkProgram()  override; // Una vez añadidos todos los programas,compila y linka para generar el programa final
	void use()  override; // Activa el uso de este programa
	void checkLinkerErrors()  override; // Muestra por terminal los errores encontrados durante la compilación y linkado
	void setColorTextEnable() override; //Inicializa la variable uniform que indicará al shader de fragmentos si debe de utilizar texturas al colorear
	void setColorTextDisable() override;
	void bindColorTextureSampler(int binding, ITexture* text) override; // Selecciona el punto de enlace (binding)para la textura pasada por parámetros


	void setVertexAttrib(std::string name, GLsizei stride, void* offset, GLint count, GLenum type)  override;
	void setInt(std::string name, int val)  override;
	void setFloat(std::string name, float val)  override;
	void setVec3(std::string name, const glm::vec3& vec)  override;
	void setVec4(std::string name, const glm::vec4& vec)  override;
	void setMatrix(std::string name, const glm::mat4& matrix)  override;
};

