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
        default:
            break;
        }
    }
}