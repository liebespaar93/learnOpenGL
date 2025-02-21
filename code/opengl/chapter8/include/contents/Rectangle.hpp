#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <vector>

class Rectangle
{
public:
    Rectangle();
    ~Rectangle();

    // Deleted copy constructor and assignment operator to prevent copying
    Rectangle(const Rectangle &) = delete;
    Rectangle &operator=(const Rectangle &) = delete;

    // Create the rectangle mesh
    void create();

    // Render the rectangle
    void render() const;

    // Check if the rectangle is initialized
    bool isInitialized() const { return m_initialized; }

private:
    void cleanup();
    void checkGLError(const char *operation) const;

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    bool m_initialized;

    // Vertex data
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

};

#endif