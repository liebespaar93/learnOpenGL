#define GL_SILENCE_DEPRECATION

#include "GlWindow.hpp"

GlWindow::GlWindow(int width, int height, const std::string &title)
    : window(nullptr), currentWidth(width), currentHeight(height), title(title)
{
}

GlWindow::~GlWindow()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}

void GlWindow::initialize(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  initGLFW();
  createWindow();

  std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

  glfwSetFramebufferSizeCallback(window, resizeCallback);

  glfwSetKeyCallback(window, keyCallback);
}

void GlWindow::resizeCallback(GLFWwindow *window, int width, int height)
{
    GlWindow* glWindow = static_cast<GlWindow*>(glfwGetWindowUserPointer(window));
    
    if (glWindow)
    {
        glWindow->currentWidth = width;
        glWindow->currentHeight = height;
        glViewport(0, 0, width, height);
    }
}

void GlWindow::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  (void)scancode;
  (void)mods;

  if (action == GLFW_PRESS)
  {
    std::cout << "Key Pressed: " << key << std::endl;
    switch (key)
    {
    case GLFW_KEY_ESCAPE:
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    default:
      break;
    }
  }
}

void GlWindow::initGLFW()
{
  if (!glfwInit())
  {
    std::cerr << "ERROR: GLFW initialization failed\n";
    std::exit(EXIT_FAILURE);
  }
}

void GlWindow::createWindow()
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(currentWidth / 2, currentHeight / 2, title.c_str(), NULL, NULL);
  if (!window)
  {
    std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // 업데이트 간격

  glfwSetWindowUserPointer(window, this); // user data에 class저장
}

void GlWindow::resize(int width, int height)
{
  currentWidth = width;
  currentHeight = height;
  glViewport(0, 0, currentWidth, currentHeight);
}

bool GlWindow::shouldClose() const
{
  return glfwWindowShouldClose(window);
}

void GlWindow::swapBuffers() const
{
  glfwSwapBuffers(window);
}

void GlWindow::pollEvents() const
{
  glfwPollEvents();
}

int GlWindow::getCurrentWidth()
{
  return this->currentWidth;
}

int GlWindow::getCurrentHeight()
{
  return this->currentHeight;
}

void KeyCallbackFunc(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  (void)scancode;
  (void)mods;

  if (action == GLFW_PRESS)
  {
    std::cout << "Key Pressed: " << key << std::endl;
    if (key == GLFW_KEY_ESCAPE)
      glfwSetWindowShouldClose(window, GLFW_TRUE);

    switch (key)
    {
    default:
      break;
    }
  }
}
