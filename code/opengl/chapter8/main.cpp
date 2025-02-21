#define GL_SILENCE_DEPRECATION

#include "main.hpp"

int main(int argc, char *argv[])
{
  CmdLineArgs argsParse = CmdLineArgs(argc, argv);

  GlWindow *glWindow = new GlWindow(600, 600, "chater 8");

  glWindow->initialize(argc, argv);

  GlShaderProgram *glShaderProgram = new GlShaderProgram("glsl/vertex_shader.vert", "glsl/fragment_shader.frag");
  glShaderProgram->use();

  // 유니폼 설정
  // glShaderProgram->getUniformLocation("u_resolution");
  // glShaderProgram->getUniformLocation("u_time");
  // glShaderProgram->getUniformLocation("u_renderMode");
  // glShaderProgram->getUniformLocation("u_stepMode");

  glShaderProgram->setUniform("u_stepMode", argsParse.holds<int>(0) ? argsParse.get<int>(0) : 0);
  glShaderProgram->setUniform("u_time", glfwGetTime());

  // 오브젝트 만들기
  Line line(glm::vec2(-1,-1), glm::vec2(1,1), 10);
  line.create();

  Rectangle rectangle;
  rectangle.create();

  // 렌더링 루프
  while (!glWindow->shouldClose())
  {
    // 배경색 설정
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glShaderProgram->setUniform("u_resolution", glWindow->getCurrentWidth(), glWindow->getCurrentHeight());

    // 쉐이더 사용
    glShaderProgram->use();

    // 렌더링
    glShaderProgram->setUniform("u_renderMode", 3);
    rectangle.render();
    glShaderProgram->setUniform("u_renderMode", 2);
    line.render();

    glWindow->swapBuffers();
    glWindow->pollEvents();
  }

  // 리소스 정리
  delete glShaderProgram;

  return 0;
}
