// Line.cpp
#define GL_SILENCE_DEPRECATION
#include "Line.hpp"
#include <iostream>

Line::Line()
    : lineVAO(0), lineVBO(0), pointSize(12.0f)
{
    // 기본 색상 초기화
    color = {0.0f, 1.0f, 0.0f, 1.0f};  // 초록색

    // 기본 버텍스 데이터 초기화
    vertices = {
        -1.0f, 0.0f, 0.0f, color.r, color.g, color.b, color.a,
         1.0f, 0.0f, 0.0f, color.r, color.g, color.b, color.a
    };
}

Line::~Line()
{
    deleteLine();
}

bool Line::create()
{
    try {
        glGenVertexArrays(1, &lineVAO);
        glBindVertexArray(lineVAO);

        glGenBuffers(1, &lineVBO);
        glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_DYNAMIC_DRAW);

        // 위치 데이터
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // 색상 데이터
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error creating line: " << e.what() << std::endl;
        return false;
    }
}

void Line::render() const
{
    glBindVertexArray(lineVAO);
    
    // 선 그리기
    glDrawArrays(GL_LINES, 0, 2);
    
    // 점 그리기
    glPointSize(pointSize);
    glDrawArrays(GL_POINTS, 0, 2);
    
    glBindVertexArray(0);
}

void Line::setColor(float r, float g, float b, float a)
{
    color = {r, g, b, a};
    
    // 색상 업데이트
    vertices[3] = vertices[10] = r;
    vertices[4] = vertices[11] = g;
    vertices[5] = vertices[12] = b;
    vertices[6] = vertices[13] = a;
    
    updateVertexBuffer();
}

void Line::setPosition(float startX, float startY, float endX, float endY)
{
    vertices[0] = startX;
    vertices[1] = startY;
    vertices[7] = endX;
    vertices[8] = endY;
    
    updateVertexBuffer();
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
    if (lineVBO != 0) {
        glDeleteBuffers(1, &lineVBO);
        lineVBO = 0;
    }
    if (lineVAO != 0) {
        glDeleteVertexArrays(1, &lineVAO);
        lineVAO = 0;
    }
}