#pragma once
#include "mapi/common.h"

class InputManager
{
public:
	static inline std::map<int, bool>keyboardState; //Mapa de carácteres para poder consultar si una tecla está apretada o no
	virtual void init(GLFWwindow* window) = 0;
	virtual bool isPressed(char key) = 0;
};

