#ifndef MAIN_HPP
#define MAIN_HPP

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include "GlWindow.hpp"
#include "GlShaderProgram.hpp"

#include "Line.hpp"
#include "Rectangle.hpp"
#include "CmdLineArgs.hpp"

void createShaderFunction();
void deleteShaderFunction();
void renderFunction(GLint renderModeLoc);

#endif