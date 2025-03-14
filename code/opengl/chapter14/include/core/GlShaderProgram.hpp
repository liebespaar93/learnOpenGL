#ifndef SHADER_HPP
#define SHADER_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

class GlShaderProgram
{
public:
    GlShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);
    ~GlShaderProgram();

    GLuint getProgram() const;
    void use() const;

    // 유니폼 설정
    GLint getUniformLocation(const std::string &name);
    void setUniform(const std::string &name, int value);
    void setUniform(const std::string &name, float value);
    void setUniform(const std::string &name, float x, float y);

    void setUniform(const std::string &name, GLdouble x);
    
private:
    GLuint program;
    std::unordered_map<std::string, GLint> uniformLocations;

    GLuint createShader(GLenum shaderType, const std::string &shaderSource);
    GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);

    std::string ReadShaderFile(std::string filename);
};

#endif
