#ifndef QUADRANGLE_H
#define QUADRANGLE_H

#include <stdlib.h>
#include <stdio.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

GLuint rectangleVAO, rectangleVBO, rectangleEBO;

void createRectangle();
void deleteRectangle();
void renderRectangle();

#endif
