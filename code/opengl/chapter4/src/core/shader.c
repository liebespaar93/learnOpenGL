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

void CreateVertices();
void CreateIndices();

GLuint CreateVBO()
{
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  CreateVertices();
  CreateIndices();

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

void CreateVertices()
{
  Vertex vertices[] = {
      {{0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
      // Top
      {{-0.2f, 0.8f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
      {{0.2f, 0.8f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
      {{0.0f, 0.8f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
      {{0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
      // Bottom
      {{-0.2f, -0.8f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
      {{0.2f, -0.8f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
      {{0.0f, -0.8f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
      {{0.0f, -1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
      // Left
      {{-0.8f, -0.2f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
      {{-0.8f, 0.2f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
      {{-0.8f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
      {{-1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
      // Right
      {{0.8f, -0.2f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
      {{0.8f, 0.2f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
      {{0.8f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
      {{1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}}};

  glGenBuffers(1, &BufferId);
  glBindBuffer(GL_ARRAY_BUFFER, BufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(vertices[0].XYZW)));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
}

void CreateIndices()
{

  GLubyte indices[] = {
      // Top
      0, 1, 3,
      0, 3, 2,
      3, 1, 4,
      3, 4, 2,
      // Bottom
      0, 5, 7,
      0, 7, 6,
      7, 5, 8,
      7, 8, 6,
      // Left
      0, 9, 11,
      0, 11, 10,
      11, 9, 12,
      11, 12, 10,
      // Right
      0, 13, 15,
      0, 15, 14,
      15, 13, 16,
      15, 16, 14};

  GLubyte alternateIndices[] = {
      // Outer square border:
      3, 4, 16,
      3, 15, 16,
      15, 16, 8,
      15, 7, 8,
      7, 8, 12,
      7, 11, 12,
      11, 12, 4,
      11, 3, 4,

      // Inner square
      0, 11, 3,
      0, 3, 15,
      0, 15, 7,
      0, 7, 11};

  glGenBuffers(2, IndexBufferId);

  printf("IndexBufferId[0]: %d, IndexBufferId[1]: %d\n", IndexBufferId[0], IndexBufferId[1]);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(alternateIndices), alternateIndices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId[0]);
}
