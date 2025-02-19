#define GL_SILENCE_DEPRECATION

#include "line.h"

GLuint createLine()
{
    GLfloat vertices[] = {
        // x, y, r, g, b, a (위치, 색상)
        -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        1.f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f};

    glGenVertexArrays(1, &lineVAO);
    glBindVertexArray(lineVAO);

    glGenBuffers(1, &lineVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 위치 데이터
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    // 색상 데이터 (in_Color)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return (lineVAO);
}

void deleteLine()
{
    glDeleteBuffers(1, &lineVBO);
    glDeleteVertexArrays(1, &lineVAO);
}

void renderLine()
{
    glBindVertexArray(lineVAO);
    glDrawArrays(GL_LINES, 0, 2);
    glPointSize(12.0f);
    glDrawArrays(GL_POINTS, 0, 2);
    glBindVertexArray(0);
}