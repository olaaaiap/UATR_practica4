#pragma once
#include "mapi/common.h"

typedef struct mouseState_t {
	double x;
	double y;
	std::map<int, bool> button;
} mouseState_t;



class InputManager
{
public:
	static inline mouseState_t mouseState;

	static inline std::map<int, bool>keyboardState; //Mapa de carácteres para poder consultar si una tecla está apretada o no
	virtual void init(GLFWwindow* window) = 0;
	virtual bool isPressed(char key) = 0;

	static bool isMousePressed(int key) {
		return mouseState.button[key];
	};
	static double getMouseX() { return mouseState.x; };
	static double getMouseY() { return mouseState.y; };
};

