#define GL_SILENCE_DEPRECATION

#include "shader.h"
#include "file_reader.h"

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

GLuint CreateShaderProgram(const char *vertexPath, const char *fragmentPath)
{
  GLuint vertexShader, fragmentShader, shaderProgram;

  char *vertexShaderSource = readShaderFile(vertexPath);
  char *fragmentShaderSource = readShaderFile(fragmentPath);

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
