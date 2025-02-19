#define GL_SILENCE_DEPRECATION

#include <stdlib.h>
#include <stdio.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "interaction.h"

#define WINDOW_TITLE_PREFIX "Chapter 2"

int CurrentWidth = 600,
    CurrentHeight = 600;

GLFWwindow *window;

void Initialize(int, char *[]);
void InitWindow(int, char *[]);
void ResizeFunction(GLFWwindow *, int, int);
void RenderFunction();

int main(int argc, char *argv[])
{
  // input 값 정의
  Initialize(argc, argv);

  // shader 프로그램 만들기
  GLuint shaderProgram = CreateShaderProgram("glsl/vertex_shader.vert", "glsl/fragment_shader.frag");

  // VBO 생성
  CreateVBO();

  // shader program을 이용하여 그림 그리기
  glUseProgram(shaderProgram);

  while (!glfwWindowShouldClose(window))
  {
    RenderFunction();
    // event queue 마우스 키보드 등의 이벤트를 수신한다
    glfwPollEvents();
  }

  // vbo 제거
  DestroyVBO();

  // shader 프로그램 삭제
  DestroyShaderProgram(shaderProgram);

  // 화면 제거
  glfwDestroyWindow(window);
  // glfw 자원 회수
  glfwTerminate();

  exit(EXIT_SUCCESS);
}

void Initialize(int argc, char *argv[])
{
  InitWindow(argc, argv);

  fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void InitWindow(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  // opengl 기본정의
  if (!glfwInit())
  {
    fprintf(stderr, "ERROR: GLFW initialization failed\n");
    exit(EXIT_FAILURE);
  }

  // 맥스 버전
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // 창 생성
  window = glfwCreateWindow(CurrentWidth, CurrentHeight, WINDOW_TITLE_PREFIX, NULL, NULL);
  if (!window)
  {
    fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // 렌더링 시작
  glfwMakeContextCurrent(window);

  // 동기화 정의
  glfwSwapInterval(1); // V-Sync

  // 리사이즈 함수 등록
  glfwSetFramebufferSizeCallback(window, ResizeFunction);

  // 키보드 활성화
  glfwSetKeyCallback(window, KeyCallbackFunc);
}

void ResizeFunction(GLFWwindow *window, int Width, int Height)
{
  (void)window;

  CurrentWidth = Width;
  CurrentHeight = Height;
  glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBindVertexArray(VAO);
  if (ActiveIndexBuffer == 0)
    glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_BYTE, NULL);
  else
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);
  glBindVertexArray(0);

  glfwSwapBuffers(window);
}
