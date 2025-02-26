#define GL_SILENCE_DEPRECATION

#include "GlShaderProgram.hpp"

GlShaderProgram::GlShaderProgram(const std::string &vertexPath, const std::string &fragmentPath)
{
    std::string vertexShaderSource = this->ReadShaderFile(vertexPath);
    std::string fragmentShaderSource = this->ReadShaderFile(fragmentPath);

    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    program = createProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GlShaderProgram::~GlShaderProgram()
{
    glDeleteProgram(program);
}

GLuint GlShaderProgram::getProgram() const
{
    return program;
}

void GlShaderProgram::use() const
{
    glUseProgram(program);
}

GLuint GlShaderProgram::createShader(GLenum shaderType, const std::string &shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    const char *source = shaderSource.c_str();
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR: Shader compilation failed\n"
                  << infoLog << std::endl;
        std::exit(-1);
    }
    return shader;
}

GLuint GlShaderProgram::createProgram(GLuint vertexShader, GLuint fragmentShader)
{
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "ERROR: Program linking failed\n"
                  << infoLog << std::endl;
        std::exit(-1);
    }

    return program;
}

std::string GlShaderProgram::ReadShaderFile(std::string filename)
{
    std::ifstream file(filename);
    std::stringstream shaderStream;

    if (file.is_open())
    {
        shaderStream << file.rdbuf();
        file.close();
    }
    else
    {
        std::cerr << "Failed to open shader file: " << filename << std::endl;
    }

    return shaderStream.str();
}

GLint GlShaderProgram::getUniformLocation(const std::string &name)
{
    if (uniformLocations.find(name) != uniformLocations.end())
        return uniformLocations[name];

    GLint location = glGetUniformLocation(program, name.c_str());
    if (location == -1)
    {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader.\n";
        return -1;
    }
    uniformLocations[name] = location;
    return location;
}

void GlShaderProgram::setUniform(const std::string &name, GLint value)
{
    GLint location = getUniformLocation(name);
    if (location != -1)
        glUniform1i(location, value);
}

void GlShaderProgram::setUniform(const std::string &name, GLfloat value)
{
    GLint location = getUniformLocation(name);
    if (location != -1)
        glUniform1f(location, value);
}

void GlShaderProgram::setUniform(const std::string &name, GLfloat x, GLfloat y)
{
    GLint location = getUniformLocation(name);
    if (location != -1)
        glUniform2f(location, x, y);
}

void GlShaderProgram::setUniform(const std::string &name, GLdouble x)
{
    GLint location = getUniformLocation(name);
    if (location != -1)
        glUniform1f(location, x);
}
