#include "FactoryEngine.h"
#include "GL1Render.h"
#include "GLFWInputManager.h"
#include "Material.h"
#include <GLFW/glfw3.h>

static constexpr double DEFAULT_WIDTH = 800.0;
static constexpr double DEFAULT_HEIGHT = 600.0;

IRender* FactoryEngine::getNewRender()
{
    switch (selectedGraphicsBackend)
    {
    case GraphicsBackend::GL1_0:
        return new GL1Render(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    case GraphicsBackend::GL4:    // NUEVO backend moderno
        return new GL4Render(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    default:
        return nullptr;
    }
}

InputManager* FactoryEngine::getNewInputManager()
{
    switch (selectedInputBackend)
    {
    case IBackend::Default:
    case IBackend::None:
    {
        GLFWInputManager* im = new GLFWInputManager();
        GLFWwindow* win = glfwGetCurrentContext();
        if (win)
            im->init(win);
        return im;
    }

    default:
        return nullptr;
    }
}

Material* FactoryEngine::getNewMaterial()
{
    switch (selectedGraphicsBackend)
    {
    case GraphicsBackend::GL4:
        return new GLSLMaterial();

    case GraphicsBackend::GL1_0:
    default:
        return nullptr;
    }
}

ITexture* FactoryEngine::getNewTexture()
{
    switch (selectedGraphicsBackend)
    {
    case GraphicsBackend::GL4:
        return new GLTexture();

    case GraphicsBackend::GL1_0:
    default:
        return nullptr;
    }
}

bool FactoryEngine::isClosed() noexcept
{
    GLFWwindow* win = glfwGetCurrentContext();
    if (!win) return true; //si no hay ventana

    return glfwWindowShouldClose(win) != 0;
}
