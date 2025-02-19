#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

typedef struct Vertex {
  float XYZW[4];
  float RGBA[4];
} Vertex;

GLuint CreateShaderProgram(const char *vertexPath, const char *fragmentPath);
void DestroyShaderProgram(GLuint shaderProgram);

GLuint VAO, VBO, ColorBuffer;

GLuint CreateVBO();
void DestroyVBO();

GLuint BufferId, IndexBufferId[2];

GLuint ActiveIndexBuffer;

#endif