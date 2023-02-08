#include "game.h"

using namespace std;

Game Game::Instance;

Game::Game() = default;

bool Game::Init() {
    glfwSetErrorCallback([](int error, const char* description) {
        cout << "Error:" << error + description << endl;
        });

    if (!glfwInit()) {
        cout << "Error: Failed to initialize GLFW!" << endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window = glfwCreateWindow(WIDTH, HEIGHT, "Skia Test", NULL, NULL);

    if (!Window) {
        cout << "Error: Failed to create window!" << endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(Window);
    glfwSwapInterval(1);

    glfwSetMouseButtonCallback(Window, MouseCallback);
    glfwSetCursorPosCallback(Window, CursorPosCallback);
    glfwSetKeyCallback(Window, KeyCallback);

    InitSkia(WIDTH, HEIGHT);

    if (!Assets::GetInstance()->GetAssetsList()) return false;

    UIManager.Init(Surface->getCanvas());

    return true;
}

void Game::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (action == GLFW_PRESS) {

    } else if (action == GLFW_RELEASE) {

    }
}

void Game::MouseCallback(GLFWwindow* window, int button, int action, int mods) {

}

void Game::CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    printf("x:%f  y:%f\n", xpos, ypos);
}

void Game::InitSkia(int width, int height) {
	auto interface = GrGLMakeNativeInterface();
	Context = GrDirectContext::MakeGL(interface).release();

	GrGLFramebufferInfo framebufferInfo;
	framebufferInfo.fFBOID = 0; 
	framebufferInfo.fFormat = GL_RGBA8;

	SkColorType colorType = kRGBA_8888_SkColorType;
	GrBackendRenderTarget backendRenderTarget(width, height, 0, 0, framebufferInfo);

	Surface = SkSurface::MakeFromBackendRenderTarget(Context, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr).release();
	if (Surface == nullptr) abort();
}

void Game::OnEvent(GLFWwindow* window) {

}

void Game::Update(int deltaTime) {
    SkCanvas* canvas = Surface->getCanvas();
    canvas->clear(SK_ColorCYAN);

    UIManager.Render();

    Context->flush();
}

void Game::Cleanup() {
    glfwTerminate();

    Assets::GetInstance()->CleanUp();

    cout << "Log: Quit!" << endl;
}

int Game::Execute(int argc, char** argv) {
    if (!Init()) {
        return 1;
    }

    double last_tick = 0;

    while (!glfwWindowShouldClose(Window))
    {
        OnEvent(Window);

        Update((int)(glfwGetTime() - last_tick));
        last_tick = glfwGetTime();

        glfwSwapBuffers(Window);
        glfwWaitEvents();
    }

    Cleanup();
    return 0;
}

Game* Game::GetInstance() {
    return &Game::Instance;
}

int Game::GetWindowWidth() {
    return WIDTH;
}

int Game::GetWindowHeight() {
    return HEIGHT;
}