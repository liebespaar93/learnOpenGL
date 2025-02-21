#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

class GlWindow
{
public:
    GlWindow(int width, int height, const std::string &title);
    ~GlWindow();

    void initialize(int argc, char *argv[]);
    void resize(int width, int height);
    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;

    int getCurrentWidth();
    int getCurrentHeight();

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

    static void resizeCallback(GLFWwindow *window, int width, int height);

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
private:
    void initGLFW();
    void createWindow();

    GLFWwindow *window;
    int currentWidth;
    int currentHeight;
    std::string title;
};

#endif
