#define GL_SILENCE_DEPRECATION

#include "Rectangle.hpp"
#include <iostream>

Rectangle::Rectangle()
    : m_vao(0), m_vbo(0), m_ebo(0), m_initialized(false)
{
    vertices = {
        -1.0f, -1.0f, 0.0f, // Bottom left
        -1.0f, 1.0f, 0.0f,  // Top left
        1.0f, -1.0f, 0.0f,  // Bottom right
        1.0f, 1.0f, 0.0f    // Top right
    };
    indices = {
        0, 1, 2, // First triangle
        2, 1, 3  // Second triangle
    };
}

Rectangle::~Rectangle()
{
    cleanup();
}

void Rectangle::create()
{
    cleanup();
    try
    {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(0);

        // Unbind buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        m_initialized = true;
    }
    catch (const std::runtime_error &e)
    {
        cleanup();
        throw std::runtime_error(std::string("Failed to create rectangle: ") + e.what());
    }
}

void Rectangle::render() const
{
    if (!m_initialized)
    {
        throw std::runtime_error("Attempting to render uninitialized rectangle");
    }

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    checkGLError("Rectangle rendering");
    glBindVertexArray(0);
}

void Rectangle::cleanup()
{
    if (m_vbo != 0)
    {
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0;
    }
    if (m_ebo != 0)
    {
        glDeleteBuffers(1, &m_ebo);
        m_ebo = 0;
    }
    if (m_vao != 0)
    {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }
    m_initialized = false;
}

void Rectangle::checkGLError(const char *operation) const
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::string errorMsg = "OpenGL error during ";
        errorMsg += operation;
        errorMsg += ": ";
        errorMsg += std::to_string(error);
        throw std::runtime_error(errorMsg);
    }
}