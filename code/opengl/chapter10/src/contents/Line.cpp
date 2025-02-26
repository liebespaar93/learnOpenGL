// Line.cpp
#define GL_SILENCE_DEPRECATION
#include "Line.hpp"
#include <iostream>

Line::Line(glm::vec2 start, glm::vec2 end, float segments)
    : lineVAO(0), lineVBO(0), pointSize(12.0f), segments(segments)
{
    glm::vec4 color = {0.0f, 1.0f, 0.0f, 1.0f};
    generateVertices(start, end, color);
}

Line::Line(glm::vec2 start, glm::vec2 end, float segments, glm::vec4 color)
    : lineVAO(0), lineVBO(0), pointSize(12.0f), segments(segments)
{
    generateVertices(start, end, color);
}

void Line::generateVertices(glm::vec2 start, glm::vec2 end, glm::vec4 color)
{
    vertices = {};
    float x = start.x;
    float y = start.y;
    float stepx = (end.x - start.x) / segments;
    float stepy = (end.y - start.y) / segments;

    for (int i = 1; i <= segments + 1; i++)
    {
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f); // Assuming this is for 3D position
        vertices.push_back(color[0]);
        vertices.push_back(color[1]);
        vertices.push_back(color[2]);
        vertices.push_back(color[3]);

        std::cout << "Vertex " << i << ": (" << x << ", " << y << ")" << std::endl;

        x += stepx;
        y += stepy;
    }

    // OpenGL buffer setup (add this to your setup code)
    glGenVertexArrays(1, &lineVAO);
    glBindVertexArray(lineVAO);

    glGenBuffers(1, &lineVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
}

Line::~Line()
{
    deleteLine();
}

bool Line::create()
{
    try
    {
        glGenVertexArrays(1, &lineVAO);
        glBindVertexArray(lineVAO);

        glGenBuffers(1, &lineVBO);
        glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_DYNAMIC_DRAW);

        // 위치 데이터
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid *)0);
        glEnableVertexAttribArray(0);

        // 색상 데이터
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error creating line: " << e.what() << std::endl;
        return false;
    }
}

void Line::render() const
{
    glBindVertexArray(lineVAO);

    // 선 그리기
    glDrawArrays(GL_LINE_STRIP, 0, segments + 1);

    // 점 그리기
    glPointSize(pointSize);
    glDrawArrays(GL_POINTS, 0, segments + 1);

    glBindVertexArray(0);
}

void Line::setPointSize(float size)
{
    pointSize = size;
}

void Line::updateVertexBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(GLfloat), vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Line::deleteLine()
{
    if (lineVBO != 0)
    {
        glDeleteBuffers(1, &lineVBO);
        lineVBO = 0;
    }
    if (lineVAO != 0)
    {
        glDeleteVertexArrays(1, &lineVAO);
        lineVAO = 0;
    }
}
