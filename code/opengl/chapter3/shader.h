#ifndef SHADER_H
#define SHADER_H

typedef struct Vertex {
  float XYZW[4];
  float RGBA[4];
} Vertex;

GLuint CreateShaderProgram();
void DestroyShaderProgram(GLuint shaderProgram);

GLuint VAO, VBO, ColorBuffer;

GLuint CreateVBO();
void DestroyVBO();

GLuint BufferId, IndexBufferId[2];

GLuint ActiveIndexBuffer;

#endif