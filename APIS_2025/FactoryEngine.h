#pragma once
//#include "GraphicsBackend.h"
#include "IRender.h"
#include "GL4Render.h"
#include "GLSLMaterial.h"
#include "GLTexture.h"
#include "ITexture.h"

// tipos de backend gráficos disponibles
enum class GraphicsBackend
{
    GL1_0, // por ahora solo GL1.0
    GL4    // NUEVO backend moderno
};

enum class InputBackend
{
    None,
    Default,
};

// Forward declarations
class IRender;
class InputManager;
class Material;

class FactoryEngine
{
public:

    using GBackend = GraphicsBackend;
    using IBackend = InputBackend;

    //Backends seleccionados
    inline static GBackend selectedGraphicsBackend = GBackend::GL1_0;
    inline static IBackend selectedInputBackend = IBackend::None;

    //Getters/Setters
    static void SetGraphicsBackend(GBackend backend) noexcept { selectedGraphicsBackend = backend; }
    static GBackend GetGraphicsBackend() noexcept { return selectedGraphicsBackend; }

    static void SetInputBackend(IBackend backend) noexcept { selectedInputBackend = backend; }
    static IBackend GetInputBackend() noexcept { return selectedInputBackend; }

    static IRender* getNewRender();
    static InputManager* getNewInputManager();

    static Material* getNewMaterial();

    static ITexture* getNewTexture();

    static bool isClosed() noexcept;
};
