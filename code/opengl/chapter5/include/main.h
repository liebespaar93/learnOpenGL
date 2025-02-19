#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "line.h"
#include "interaction.h"

int CurrentWidth = 600,
    CurrentHeight = 600;

GLFWwindow *window;

void Initialize(int, char *[]);
void InitWindow(int, char *[]);
void ResizeFunction(GLFWwindow *, int, int);
void RenderFunction();

#endif