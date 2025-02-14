#define GL_SILENCE_DEPRECATION

#include <stdio.h>
#include <stdlib.h>

#include "interaction.h"

void KeyCallbackFunc(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;

    if (action == GLFW_PRESS)
    {
        printf("Key Pressed: %d\n", key);
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GLFW_TRUE);

        switch (key)
        {
        case 'T':
        case 't':
        {
            ActiveIndexBuffer = (ActiveIndexBuffer == 1 ? 0 : 1);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId[ActiveIndexBuffer]);
            glBindVertexArray(0);
            break;
        }
        default:
            break;
        }
    }
}