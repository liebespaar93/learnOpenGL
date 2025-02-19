#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include "init.h"
#include "shader.h"
#include "line.h"
#include "quadrangle.h"
#include "interaction.h"

void createShaderFunction();
void deleteShaderFunction();
void renderFunction(GLint renderModeLoc);

#endif