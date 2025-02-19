#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

GLuint CreateShaderProgram(const char *vertexPath, const char *fragmentPath);
void DestroyShaderProgram(GLuint shaderProgram);

#endif