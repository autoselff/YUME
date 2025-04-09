#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "keycodes.h"

namespace yume {

    void updateInput();

    bool keyPressed(unsigned int keycode);

    bool keyDown(unsigned int keycode);

    bool keyReleased(unsigned int keycode);
}