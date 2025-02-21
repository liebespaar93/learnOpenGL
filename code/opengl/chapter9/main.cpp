#define GL_SILENCE_DEPRECATION

#include "main.hpp"

int main(int argc, char *argv[])
{
  CmdLineArgs argsParse = CmdLineArgs(argc, argv);

  GlWindow *glWindow = new GlWindow(1200, 700, "chater 8");

  glWindow->initialize(argc, argv);

  GlShaderProgram *glSinShaderProgram = new GlShaderProgram("glsl/sin_vertex_shader.vert", "glsl/sin_fragment_shader.frag");
  glSinShaderProgram->setUniform("u_time", glfwGetTime());

  Line sinLine(glm::vec2(-1, 1), glm::vec2(1, -1), 30, glm::vec4(1.0, 0.0, 0.0, 1.0));
  sinLine.create();

  GlShaderProgram *glCosShaderProgram = new GlShaderProgram("glsl/cos_vertex_shader.vert", "glsl/cos_fragment_shader.frag");
  glCosShaderProgram->setUniform("u_time", glfwGetTime());

  Line cosLine(glm::vec2(-1, -1), glm::vec2(1, 1), 100);
  cosLine.create();

  GlShaderProgram *glCricleShaderProgram = new GlShaderProgram("glsl/circle_vertex_shader.vert", "glsl/circle_fragment_shader.frag");
  Line cricleLine(glm::vec2(-1, -1), glm::vec2(1, 1), 100, glm::vec4(1.0, 1.0, 0.0, 1.0));
  cricleLine.create();

  // 렌더링 루프
  while (!glWindow->shouldClose())
  {
    // 배경색 설정
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // sin 그리기
    glSinShaderProgram->setUniform("u_time", glfwGetTime());

    glSinShaderProgram->setUniform("u_resolution", glWindow->getCurrentWidth(), glWindow->getCurrentHeight());
    glSinShaderProgram->use();
    sinLine.render();

    // cos 그리기
    glCosShaderProgram->setUniform("u_time", glfwGetTime());

    glCosShaderProgram->setUniform("u_resolution", glWindow->getCurrentWidth(), glWindow->getCurrentHeight());
    glCosShaderProgram->use();
    cosLine.render();

    // 원 그리기
    glCricleShaderProgram->setUniform("u_time", glfwGetTime());
    glCricleShaderProgram->setUniform("u_resolution", glWindow->getCurrentWidth(), glWindow->getCurrentHeight());
    glCricleShaderProgram->use();
    cricleLine.render();

    glWindow->swapBuffers();
    glWindow->pollEvents();
  }

  // 리소스 정리
  delete glSinShaderProgram;
  delete glCosShaderProgram;

  return 0;
}
