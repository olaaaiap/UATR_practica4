#include "GLSLProgram.h"
#include "GLSLShader.h"


void GLSLProgram::readVarList() {

    int numAttributes = 0;
    int numUniforms = 0;
    glGetProgramiv(programId, GL_ACTIVE_ATTRIBUTES, &numAttributes);
    for (int i = 0; i < numAttributes; i++)
    {
        char varName[100];
        int bufSize = 100, length = 0, size = 0;
        GLenum type = -1;
        glGetActiveAttrib(programId, (GLuint)i, bufSize, &length, &size, &type, varName);
        varList[std::string(varName)] = glGetAttribLocation(programId, varName);
    }

    glGetProgramiv(programId, GL_ACTIVE_UNIFORMS, &numUniforms);
    for (int i = 0; i < numUniforms; i++)
    {
        char varName[100];
        int bufSize = 100, length = 0, size = 0;
        GLenum type = -1;
        glGetActiveUniform(programId, (GLuint)i, bufSize, &length, &size, &type,
            varName);
        varList[std::string(varName)] = glGetUniformLocation(programId, varName);
    }
}

unsigned int GLSLProgram::getVarLocation(const std::string& name)
{
    if (varList.find(name) != varList.end())
        return varList[name];
    else {
        std::cout << "ERROR: variable " << name <<
            " no encontrada en shader\n";
        return -1;
    }
}


void GLSLProgram::addProgram(std::string fileName)
{
    programTypes_e type = programTypes_e::fragment;
    if (fileName.size() >= 5) {
        if (fileName.rfind(".vert") == fileName.size() - 5) type = programTypes_e::vertex;
        else if (fileName.rfind(".frag") == fileName.size() - 5) type = programTypes_e::fragment;
    }

    GLSLShader* shader = new GLSLShader(fileName, type);
    shaders.push_back(static_cast<IProgram*>(shader));
}

//void GLSLProgram::linkProgram()
//{
//    //crear programa
//    programId = glCreateProgram();
//
//    //por cada shader en shaderList
//    for (auto& c : shaders)
//    {
//        //compilar
//        GLSLShader shader(c->fileName, c->type);
//        if (shader.compiled)
//        {
//            //atar al programa
//            glAttachShader(programId, shader.idProgram);
//        }
//    }
//    //linkar programas
//    glLinkProgram(programId);
//
//	checkLinkerErrors();
//
//    readVarList();
//    //limpiar datos
//}
void GLSLProgram::linkProgram()
{
    programId = glCreateProgram();

    for (auto& p : shaders)
    {
        auto* shader = dynamic_cast<GLSLShader*>(p);
        if (!shader) continue;

        if (!shader->compiled)
            shader->compile();

        if (shader->compiled)
            glAttachShader(programId, shader->idProgram);
        else
            std::cout << "ERROR: Shader no compilado: " << shader->fileName << "\n";
    }

    glLinkProgram(programId);
    checkLinkerErrors();

    if (linked)
        readVarList();
}

void GLSLProgram::use()
{
    if (!linked) {
        std::cout << "ERROR: El programa GLSL no está linkado\n";
        return;
    }

    //activar este programa
    glUseProgram(this->programId);
}

void GLSLProgram::checkLinkerErrors()
{
    //test error linkados
    GLint program_linked;
    glGetProgramiv(programId, GL_LINK_STATUS, &program_linked);
    if (program_linked != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(programId, 1024, &log_length, message);
        std::cout << "ERROR Linkando programa \"" << message << "\"\n";
    }
    else {
        linked = true;
    }
}

void GLSLProgram::setColorTextEnable()
{
    glUniform1i(varList["useColorText"], 1); //usar en shader
}

void GLSLProgram::setColorTextDisable()
{
    glUniform1i(varList["useColorText"], 0); //usar en shader
}

void GLSLProgram::bindColorTextureSampler(int binding, ITexture* text)
{
    GLenum textureType = text->getCubemap() ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D;

    glActiveTexture(GL_TEXTURE0 + binding); //activar
    glBindTexture(textureType, text->getTextID()); //enlazar

    switch (textureType)
    {
        case GL_TEXTURE_2D:
        {
            glUniform1i(varList["colorText"], binding); //usar en shader
            glUniform1i(varList["textureType"], 0); //usar en shader
        }break;
        case GL_TEXTURE_CUBE_MAP:
        {
            glUniform1i(varList["textSamplerCube"], binding); //usar en shader
            glUniform1i(varList["textureType"], 1); //usar en shader

        }break;
    }

    //glUniform1i(varList["colorText"], binding); //usar en shader
}

void GLSLProgram::setVertexAttrib(std::string name, GLsizei stride, void* offset, GLint count, GLenum type)
{
    //si existe
    if (varList.find(name) != varList.end()) {
        //activar variable atributo

        glEnableVertexAttribArray(varList[name]);
        // 
        //describir variable atributo
        glVertexAttribPointer(varList[name], count, type, GL_FALSE, stride, offset);
    }
    else {
        std::cout << "ERROR Atributo " << name << " no encontrado\n";
    }
}

void GLSLProgram::setInt(std::string name, int val)
{
    //si existe
    if (varList.find(name) != varList.end()) {
        glUniform1i(varList[name], val);
    }
    else {
        std::cout << "ERROR Atributo " << name << " no encontrado\n";
    }
}

void GLSLProgram::setFloat(std::string name, float val)
{
    //si existe
    if (varList.find(name) != varList.end()) {
        glUniform1f(varList[name], val);
    }
    else {
        std::cout << "ERROR Atributo " << name << " no encontrado\n";
    }
}

void GLSLProgram::setVec3(std::string name, const glm::vec3& vec)
{
    //si existe
    if (varList.find(name) != varList.end()) {
        glUniform3fv(varList[name], 1, &vec[0]);
    }
    else {
        std::cout << "ERROR Atributo " << name << " no encontrado\n";
    }
}

void GLSLProgram::setVec4(std::string name, const glm::vec4& vec)
{
    //si existe
    if (varList.find(name) != varList.end()) {
        glUniform4fv(varList[name], 1, &vec[0]);
    }
    else {
        std::cout << "ERROR Atributo " << name << " no encontrado\n";
    }
}

void GLSLProgram::setMatrix(std::string name, const glm::mat4& matrix)
{
    //si existe
    if (varList.find(name) != varList.end()) {
        //actualizar variable uniform
        glUniformMatrix4fv(varList[name], 1, false, &matrix[0][0]);
    }
    else {
        std::cout << "ERROR Atributo " << name << " no encontrado\n";
    }
}
