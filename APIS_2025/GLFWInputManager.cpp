#include "GLFWInputManager.h"


void GLFWInputManager::init(GLFWwindow* window)
{
	glfwSetKeyCallback(window, GLFWInputManager::windowKeyboardEvent);
	glfwSetMouseButtonCallback(window, GLFWInputManager::mouseButtonEvent);
	glfwSetCursorPosCallback(window, GLFWInputManager::mousePosEvent);
	GLFWInputManager::window = window;
	glfwSetCursorPos(window, 0, 0);
}

//void GLFWInputManager::setKMCursorPos(double x, double y)
//{
//	mouseState.xPos = x; mouseState.yPos = y;
//	glfwSetCursorPos(window, x, y);
//}

void GLFWInputManager::windowKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
	{
		keyboardState[key] = true;

	}break;

	case GLFW_RELEASE:
	{
		keyboardState[key] = false;

	}break;

	}

}
void GLFWInputManager::mousePosEvent(GLFWwindow* window, double xpos, double ypos)
{
	mouseState.xPos = xpos;
	mouseState.yPos = ypos;
}

void GLFWInputManager::mouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
	{
		mouseState.buttonState[button] = true;
	}break;

	case GLFW_RELEASE:
	{
		mouseState.buttonState[button] = false;
	}break;
	}
}

bool GLFWInputManager::isPressed(char key)
{
	if (keyboardState[key])
	{
		return true;
	}
	return false;
}


//void GLFWInputManager::updateEvents()
//{
//	glfwPollEvents();
//}