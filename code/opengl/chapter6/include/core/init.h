#ifndef INIT_H
#define INIT_H

#include <stdlib.h>
#include <stdio.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

GLFWwindow *window;

int currentWidth;
int currentHeight;

void Initialize(int, char *[]);
void InitWindow(int, char *[]);
void ResizeFunction(GLFWwindow *, int, int);
void RenderFunction();

#endif
