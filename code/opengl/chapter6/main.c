#define GL_SILENCE_DEPRECATION

#include "main.h"

int main(int argc, char *argv[])
{
  /* 생성 부분 */
  // input 값 정의
  Initialize(argc, argv);

  // 키보드 활성화
  glfwSetKeyCallback(window, KeyCallbackFunc);

  // shader 프로그램 만들기
  GLuint shaderProgram = CreateShaderProgram("glsl/vertex_shader.vert", "glsl/fragment_shader.frag");
  glUseProgram(shaderProgram);

  /* shader 생성부분*/
  createShaderFunction();
  /* bind 부분 */
  GLint resolutionLoc = glGetUniformLocation(shaderProgram, "u_resolution");
  glUniform2f(resolutionLoc, currentWidth, currentHeight);

  GLint timeLoc = glGetUniformLocation(shaderProgram, "u_time");
  glUniform1f(timeLoc, glfwGetTime());

  GLint renderModeLoc = glGetUniformLocation(shaderProgram, "u_renderMode");
  glUniform1i(renderModeLoc, 0); // 없음
  // glUniform1i(renderModeLoc, 1); // 점
  // glUniform1i(renderModeLoc, 2); // 선
  // glUniform1i(renderModeLoc, 3); // 삼각

  GLint stepLoc = glGetUniformLocation(shaderProgram, "u_stepMode");
  // glUniform1i(stepLoc, 0); // 없음
  // glUniform1i(stepLoc, 1); // 선
  // glUniform1i(stepLoc, 2); // 제곱

  char *endptr;
  long num;
  if (argc > 1)
  {
    num = strtol(argv[1], &endptr, 10);
    if (*endptr == '\0')
      glUniform1i(stepLoc, num);
  }

  /* 랜더링 부분 */
  while (!glfwWindowShouldClose(window))
  {
    glUniform2f(resolutionLoc, currentWidth, currentHeight);
    renderFunction(renderModeLoc);
    // event queue 마우스 키보드 등의 이벤트를 수신한다
    glfwPollEvents();
  }

  /* shader 제거 부분 */
  deleteShaderFunction();

  /* 시스템 제거 부분 */
  // shader 프로그램 삭제
  DestroyShaderProgram(shaderProgram);
  // 화면 제거
  glfwDestroyWindow(window);
  // glfw 자원 회수
  glfwTerminate();

  exit(EXIT_SUCCESS);
}

void createShaderFunction()
{
  createLine();
  createRectangle();
}

void deleteShaderFunction()
{
  deleteLine();
  deleteRectangle();
}

void renderFunction(GLint renderModeLoc)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUniform1i(renderModeLoc, 3); // 삼각
  renderRectangle();
  glUniform1i(renderModeLoc, 2); // 선
  renderLine();
  glfwSwapBuffers(window);
}
