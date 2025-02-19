
#ifndef SHADER_H
#define SHADER_H

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

GLuint CreateShaderProgram();
void DestroyShaderProgram(GLuint shaderProgram);

GLuint VAO, VBO, ColorBuffer;

GLuint CreateVBO();
void DestroyVBO();

#endif
