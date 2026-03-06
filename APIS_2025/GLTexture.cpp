#include "GLTexture.h"

void GLTexture::update()
{
    //cargar imagen en GPU
            //generar id de textura de OPENGL
    glGenTextures(1, &GlTextID);
    glBindTexture(GL_TEXTURE_2D, GlTextID);

    setTextID(GlTextID);

    //cargar en GPU datos de textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getW(), getH(), 0, GL_RGBA, GL_UNSIGNED_BYTE, getTexBytes().data());


    //activar filtros
    if (getBilinear()) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    //configurar uso
    if (getRepeat()) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    //generar mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);
    //liberar datos de cpu
    //stbi_image_free(data);


    // desbind para dejar estado limpio
    glBindTexture(GL_TEXTURE_2D, 0);




}
