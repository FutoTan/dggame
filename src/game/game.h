#include <iostream>
#include <thread>
#include <GLFW/glfw3.h>
#include <skia/gpu/GrBackendSurface.h>
#include <skia/gpu/GrDirectContext.h>
#include <skia/gpu/gl/GrGLInterface.h>
#include "assets.h"
#include "ui_manager.h"

#ifndef THGAME_GAME_H
#define THGAME_GAME_H

class Game {
private:
    static Game Instance;

    bool Running = true;
    GLFWwindow* Window = nullptr;

    GrDirectContext* Context = nullptr;
    SkSurface* Surface = nullptr;

    thread RenderThread;

    UIManager UIManager;

    const int WIDTH = 1280;
    const int HEIGHT = 960;

private:
    Game();

    void OnEvent(GLFWwindow* window);

    void InitSkia(int width, int height);

    bool Init();

    static void MouseCallback(GLFWwindow* window, int button, int action, int mods);

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);

    void Update(int deltaTime);

    void Cleanup();

public:
    int Execute(int argc, char* argv[]);

public:
    static Game* GetInstance();

    int GetWindowWidth();

    int GetWindowHeight();

};
#endif