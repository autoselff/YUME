#include "input.h"

namespace yume {
    bool keyPressedBool[372];
    bool keyDownBool[372];
    bool keyDownLastFrame[372];
    bool keyReleasedBool[372];

    void updateInput(GLFWwindow* window) {
        for (int i = 30; i < 350; i++) {
            keyDownBool[i] = (glfwGetKey(window, i) == GLFW_PRESS);
            keyPressedBool[i] = (keyDownBool[i] && !keyDownLastFrame[i]);
            keyReleasedBool[i] = (!keyDownBool[i] && keyDownLastFrame[i]);
            keyDownLastFrame[i] = keyDownBool[i];
        }
    }

    bool keyPressed(unsigned int keycode) {
        return keyPressedBool[keycode];
    }

    bool keyDown(unsigned int keycode) {
        return keyDownBool[keycode];
    }

    bool keyReleased(unsigned int keycode) {
        return keyReleasedBool[keycode];
    }
}