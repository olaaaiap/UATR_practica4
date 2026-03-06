#define STB_IMAGE_IMPLEMENTATION
#include "ITexture.h"
#include "stb_image.h"


ITexture::ITexture()
    : textID(textureCounter++), w(0), h(0), cubemap(false), bilinear(false), repeat(true)
{
    size = glm::ivec2(0, 0);
	texBytes.clear();
    fileName = "";
}

ITexture::ITexture(std::string fileName)
    : textID(textureCounter++), w(0), h(0), cubemap(false), bilinear(false), repeat(true)
{
    size = glm::ivec2(0, 0);
    texBytes.clear();
	this->fileName = fileName;
	load(fileName);
}

void ITexture::load(std::string filename)
{
	this->fileName = filename;
    //cargar imagen de fichero
    int componentes = 0;

    unsigned char* data = stbi_load(fileName.c_str(), &w, &h, &componentes, 4);
    if (data) {
        size = glm::ivec2(w, h);

        texBytes.resize(w * h * 4);
        memcpy(texBytes.data(), data, w * h * 4);
        // liberar datos cargados por stb (ya copiados a texBytes)
        stbi_image_free(data);
    }
    else {
        std::cout << "ERROR: Fichero " << fileName << " no encontrado\n";
    }
}
