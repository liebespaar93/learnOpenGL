#define GL_SILENCE_DEPRECATION

#include "main.hpp"

int main(int argc, char *argv[])
{
  CmdLineArgs argsParse = CmdLineArgs(argc, argv);

  GlWindow *glWindow = new GlWindow(700, 700, "chater 11");

  
  glWindow->initialize(argc, argv);

  GlShaderProgram *glRecShaderProgram = new GlShaderProgram("glsl/base_vertex_shader.vert", "glsl/base_fragment_shader.frag");

  Rectangle bgRectagle = Rectangle();
  bgRectagle.create();

  // 렌더링 루프
  while (!glWindow->shouldClose())
  {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glRecShaderProgram->use();

    glRecShaderProgram->setUniform("u_time", glfwGetTime());
    glRecShaderProgram->setUniform("u_resolution", glWindow->getCurrentWidth(), glWindow->getCurrentHeight());

    bgRectagle.render();

    glWindow->swapBuffers();
    glWindow->pollEvents();
  }

  // 리소스 정리
  delete glRecShaderProgram;

  return 0;
}
