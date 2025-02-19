#define GL_SILENCE_DEPRECATION

#include "quadrangle.h"

GLuint rectangleVAO, rectangleVBO;

void createRectangle()
{
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2,  // 첫 번째 삼각형
        2, 1, 3   // 두 번째 삼각형
        };

    // VAO 생성
    glGenVertexArrays(1, &rectangleVAO);
    glBindVertexArray(rectangleVAO);

    // VBO 생성
    glGenBuffers(1, &rectangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rectangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &rectangleEBO);
    // EBO에 인덱스 데이터 바인딩
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangleEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void deleteRectangle()
{
    glDeleteBuffers(1, &rectangleVBO);
    glDeleteBuffers(1, &rectangleEBO);
    glDeleteVertexArrays(1, &rectangleVAO);
}

void renderRectangle()
{
    glBindVertexArray(rectangleVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}