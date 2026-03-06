#pragma once
#include "mapi/common.h"

class ITexture
{
	static inline int textureCounter = 0;


	uint32_t textID; //Identificador único de la textura.Se debe inicializar al llamar al constructor, usando un contador que devuelva un integer no repetido
	glm::ivec2 size; //Tamaño en píxeles a lo largo de los ejes X / Y
	bool cubemap = false; //Variable booleana para indicar si es una textura cúbica(de momento, false)
	std::vector<unsigned char> texBytes; //Vector que almacena los bytes consecutivos “en bruto”de la textura cargada de fichero
	std::string fileName; //Nombre del fichero cargado
	bool bilinear = false; //Variable que indica si se debe aplicar un filtro bilinear
	bool repeat = true; //Variable que indica si las coordenadas de textura mayores que 1.0 o menores que 0.0 deben ser cíclicas a lo largo de los ejes X / Y

	int w;
	int h;

public:

	uint32_t getTextID() { return textID; };
	glm::ivec2 getSize() { return size; };
	bool getCubemap() { return cubemap; };
	std::vector<unsigned char> getTexBytes() { return texBytes; };
	std::string getFileName() { return fileName; };
	bool getBilinear() { return bilinear; };
	bool getRepeat() { return repeat; };
	int getW() { return w; };
	int getH() { return h; };

	void setTextID(uint32_t id) { textID = id; };
	void setSize(glm::ivec2 s) { size = s; };
	void setCubemap(bool c) { cubemap = c; };
	void setTexBytes(std::vector<unsigned char> bytes) { texBytes = bytes; };
	void setFileName(std::string name) { fileName = name; };
	void setBilinear(bool b) { bilinear = b; };
	void setRepeat(bool r) { repeat = r; };
	void setW(int width) { w = width; };
	void setH(int height) { h = height; };

	ITexture(); //Constructor por defecto(sin parámetros).Asigna un identificador único a textId
	ITexture(std::string fileName); //Constructor que recibe un nombre de fichero, asignará un identificador único a textID y llamara al método de carga de datos de fichero
	void load(std::string filename);//	Método que, dado un nombre de fichero, lo abrirá usando la librería stbi y cargará los datos del fichero en el vector “texBytes”
	virtual void update() = 0;

};