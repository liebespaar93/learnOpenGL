#ifndef LINE_H
#define LINE_H

#include <stdlib.h>
#include <stdio.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>


GLuint lineVAO, lineVBO;
GLuint createLine();

void deleteLine();
void renderLine();
#endif