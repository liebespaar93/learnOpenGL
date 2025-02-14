#define GL_SILENCE_DEPRECATION

#include <stdlib.h>
#include <stdio.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#define WINDOW_TITLE_PREFIX "Chapter 1"

int CurrentWidth = 800,
    CurrentHeight = 600;

GLFWwindow *window;

void Initialize(int, char *[]);
void InitWindow(int, char *[]);
void ResizeFunction(GLFWwindow *, int, int);
void RenderFunction(void);

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  // input 값 정의
  Initialize(argc, argv);

  while (!glfwWindowShouldClose(window))
  {
    RenderFunction();
    glfwPollEvents();
  }

  // 화면 제거
  glfwDestroyWindow(window);
  // glfw 자원 회수
  glfwTerminate();

  exit(EXIT_SUCCESS);
}

void Initialize(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
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
}

void ResizeFunction(GLFWwindow *window, int Width, int Height)
{
  (void)window;
  
  CurrentWidth = Width;
  CurrentHeight = Height;
  glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // 화면 출력
  glfwSwapBuffers(window);
}
