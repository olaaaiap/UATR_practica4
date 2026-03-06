#include "GLSLShader.h"

GLSLShader::GLSLShader(std::string fileName, programTypes_e type)
{
	this->fileName = fileName;
	this->type = type;
	this->idProgram = -1;

	readFile();
	if (code != "") 
	{
		//determinar tipo de shader
		if (fileName.ends_with(".vert")) {
			this->type = programTypes_e::vertex;
		}
		if (fileName.ends_with(".frag")) {
			this->type = programTypes_e::fragment;
		}

		compile();
	}
}

void GLSLShader::readFile()
{
	std::ifstream f(fileName);
	if (f.is_open()) {
		code = std::string(std::istreambuf_iterator<char>(f), {}); //Esto devuelve el texo/código que ha leido.
		f.close();
	}
	else {
		std::cout << "ERROR: FICHERO NO ENCONTRADO " <<
			__FILE__ << ":" << __LINE__ << " " << fileName << "\n";
	}
}

void GLSLShader::compile()
{
	unsigned int shaderType;

	if (type == programTypes_e::vertex) {
		shaderType = GL_VERTEX_SHADER;
	}
	else if (type == programTypes_e::fragment) {
		shaderType = GL_FRAGMENT_SHADER;
	}


	//compilar
			//crear identificador
	this->idProgram = glCreateShader(shaderType);
	
	const char* c = code.c_str();
	
	glShaderSource(idProgram, 1, &c, nullptr); //No hace falta fileSize
	glCompileShader(idProgram);

	//detectar errores de compilado
	GLint retCode;
	char errorLog[1024];
	GLint fragment_compiled;
	glGetShaderiv(idProgram, GL_COMPILE_STATUS, &fragment_compiled);
	if (fragment_compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(idProgram, 1024, &log_length, message);
		std::cout << "ERROR " << fileName << "\n" << message << "\n\n";
	}
	else
	{
		compiled = true;
	}
	

}

void GLSLShader::checkErrors() {
	GLint fragment_compiled;
	glGetShaderiv(idProgram, GL_COMPILE_STATUS, &fragment_compiled);
	if (fragment_compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(idProgram, 1024, &log_length, message);
		std::cout << "ERROR " << fileName << "\n" << message << "\n\n";
	}
}

