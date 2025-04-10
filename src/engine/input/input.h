#pragma once

#include "../config/config.h"
#include "keycodes.h"

namespace yume {

    void updateInput(GLFWwindow* window);

    bool keyPressed(unsigned int keycode);

    bool keyDown(unsigned int keycode);

    bool keyReleased(unsigned int keycode);
}