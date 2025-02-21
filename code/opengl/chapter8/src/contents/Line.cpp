// Line.cpp
#define GL_SILENCE_DEPRECATION
#include "Line.hpp"
#include <iostream>

Line::Line(glm::vec2 start, glm::vec2 end, float segments)
    : lineVAO(0), lineVBO(0), pointSize(12.0f), segments(segments)
{
    color = {0.0f, 1.0f, 0.0f, 1.0f};
    vertices = {};

    float x = start.x;
    float y = start.y;
    float stepx = (end.x - start.x) / segments;
    float stepy = (end.y - start.y) / segments;
    // 시작점과 끝점 사이를 균일하게 나누기
    for (int i = 1; i <= segments + 1; i++)
    {
        // 선형 보간으로 각 점의 위치 계산
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);
        vertices.push_back(color.r);
        vertices.push_back(color.g);
        vertices.push_back(color.b);
        vertices.push_back(color.a);
        
        // 디버그 출력 추가
        std::cout << "Vertex " << i << ": (" << x << ", " << y << ")" << std::endl;
        
        x += stepx;
        y += stepy;
    }
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
