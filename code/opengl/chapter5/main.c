#define GL_SILENCE_DEPRECATION

#define WINDOW_TITLE_PREFIX "Chapter 5"

#include "main.h"

int main(int argc, char *argv[])
{
  /* 생성 부분 */
  // input 값 정의
  Initialize(argc, argv);

  // shader 프로그램 만들기
  GLuint shaderProgram = CreateShaderProgram("glsl/vertex_shader.vert", "glsl/fragment_shader.frag");
  glUseProgram(shaderProgram);

  /* shader 생성부분*/
  CreateLine();
  
  /* bind 부분 */
  GLint resolutionLoc = glGetUniformLocation(shaderProgram, "u_resolution");
  glUniform2f(resolutionLoc, 800.0f, 600.0f);

  GLint timeLoc = glGetUniformLocation(shaderProgram, "u_time");
  glUniform1f(timeLoc, glfwGetTime());

  /* 랜더링 부분 */
  while (!glfwWindowShouldClose(window))
  {
    RenderFunction();
    // event queue 마우스 키보드 등의 이벤트를 수신한다
    glfwPollEvents();
  }

  /* shader 제거 부분 */
  DeleteLine();

  /* 시스템 제거 부분 */
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
  // 화면 정의
  InitWindow(argc, argv);

  fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

  // 리사이즈 함수 등록
  glfwSetFramebufferSizeCallback(window, ResizeFunction);

  // 키보드 활성화
  glfwSetKeyCallback(window, KeyCallbackFunc);

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
  RenderLine();
  glfwSwapBuffers(window);
}
