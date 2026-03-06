#pragma once
#include <vector>
#include <string>
#include "IRenderProgram.h"


class Material 
{
protected:
	IRenderProgram* program; // Puntero al programa de renderizado asociado a este material
	ITexture* colorText; // Puntero a la textura asociada a este material
	glm::vec4 colorRGBA; // Color básico de la malla

public:
	IRenderProgram* getProgram() { return program; } // Método para obtener el programa de renderizado asociado a este material
	ITexture* getColorText() { return colorText; } 
	void setColorText(ITexture* text) { colorText = text; }

	void setColorRGBA(glm::vec4& color) { colorRGBA = color; }
	glm::vec4 getColorRGBA() { return colorRGBA; }

	virtual void loadPrograms(const std::vector<std::string>& files) = 0; // Método virtual puro para cargar los programas de renderizado desde archivos
	virtual void prepare() = 0; // Método virtual puro para preparar el material antes de su uso (por ejemplo, configurar uniformes, texturas, etc.)
};
