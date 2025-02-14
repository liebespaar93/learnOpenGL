#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "shader.h"

const char *GlErrorString(GLenum errorCode)
{
  switch (errorCode)
  {
  case GL_NO_ERROR:
    return "No error has been recorded.";
  case GL_INVALID_ENUM:
    return "An unacceptable value is specified for an enumerated argument.";
  case GL_INVALID_VALUE:
    return "A numeric argument is out of range.";
  case GL_INVALID_OPERATION:
    return "The specified operation is not allowed in the current state.";
  case GL_OUT_OF_MEMORY:
    return "There is not enough memory left to execute the command.";
  default:
    return "Unknown error.";
  }
}
const char *vertexShaderSource = {
    "#version 400 core\n"
    "layout(location = 0) in vec4 position;\n"
    "layout(location = 1) in vec4 in_Color;\n"
    "out vec4 ex_Color;\n"
    "void main() {\n"
    "    gl_Position = position;\n"
    "    ex_Color = in_Color;\n"
    "}\n"};
    
const char *fragmentShaderSource = {
    "#version 400 core\n"
    "in vec4 ex_Color;\n"
    "out vec4 out_Color;\n"
    "void main() {\n"
    "    out_Color = ex_Color;\n"
    "}\n"};

GLuint createShader(GLenum shaderType, const char *shaderSource)
{
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &shaderSource, NULL);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    char infoLog[512];
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    fprintf(stderr, "ERROR: Shader compilation failed\n%s\n", infoLog);
    exit(-1);
  }
  return shader;
}

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader)
{
  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success)
  {
    char infoLog[512];
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    fprintf(stderr, "ERROR: Program linking failed\n%s\n", infoLog);
    exit(-1);
  }
  return program;
}

GLuint CreateShaderProgram()
{
  GLuint vertexShader, fragmentShader, shaderProgram;
  // 셰이더 프로그램 생성
  vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
  fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
  shaderProgram = createProgram(vertexShader, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
};

void DestroyShaderProgram(GLuint shaderProgram)
{
  glDeleteProgram(shaderProgram);
}

/**
 * @brief 버텍스의 버퍼를 생성한다.
 */
GLuint CreateVBO()
{
  // 정점 데이터이다
  GLfloat vertices[] = {
      -0.8f, -0.8f, 0.0f, 1.0f,
      0.0f, 0.8f, 0.0f, 1.0f,
      0.8f, -0.8f, 0.0f, 1.0f};

  // 색 데이터 이다.
  GLfloat colors[] = {
      1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f, 1.0f};

  // VAO 갯수와 주소를 전달하여 array생성
  glGenVertexArrays(1, &VAO);

  // Bind할 VAO array를 선택한다
  glBindVertexArray(VAO);

  // VAO array에 정점 정의

  // 생성할 갯수와 주소를 담을 객체를 전달하여 버퍼 생성
  glGenBuffers(1, &VBO);

  // 바인딩 과정(동기화 과정) 이 있다고 한다
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // 정점에 대한 데이터를 업데이트 해줍니다.
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // 정점 데이터 (VBO)
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)0);
  // 정점을 index를 정의하여 활성화 한다.
  glEnableVertexAttribArray(0);

  // 정점 정의 끝

  // 색 정의
  glGenBuffers(1, &ColorBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, ColorBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)0);

  glEnableVertexAttribArray(1);

  // 설정 끝
  glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO unbind 설정
  glBindVertexArray(0);             // VAO unbind 설정

  GLenum ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    fprintf(
        stderr,
        "ERROR: Could not create a VBO: %s \n",
        GlErrorString(ErrorCheckValue));
    exit(-1);
  }

  return (VAO);
}

void DestroyVBO()
{

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // 정점 비활성화
  glDisableVertexAttribArray(0);
  // 색 비활성화
  glDisableVertexAttribArray(1);

  // 버퍼 삭제
  glDeleteBuffers(1, &ColorBuffer);
  glDeleteBuffers(1, &VBO);

  // VAO array 삭제
  glDeleteVertexArrays(1, &VAO);

  GLenum ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    fprintf(
        stderr,
        "ERROR: Could not destroy the VBO: %s \n",
        GlErrorString(ErrorCheckValue));
    exit(-1);
  }
}
