#define GL_SILENCE_DEPRECATION

#define WINDOW_TITLE_PREFIX "Chapter 5"

#include "init.h"

void Initialize(int argc, char *argv[])
{
  // 화면 정의
  InitWindow(argc, argv);

  fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

  // 리사이즈 함수 등록
  glfwSetFramebufferSizeCallback(window, ResizeFunction);

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
  currentWidth = 1200;
  currentHeight = 1200;
  window = glfwCreateWindow(currentWidth/2, currentHeight/2, WINDOW_TITLE_PREFIX, NULL, NULL);

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
}

void ResizeFunction(GLFWwindow *window, int width, int height)
{
  (void)window;

  currentWidth = width;
  currentHeight = height;

  glViewport(0, 0, currentWidth, currentHeight);
}