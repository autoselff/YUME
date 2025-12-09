#pragma once

#include "../config/config.h"

class Renderer;

void mouseCallback(GLFWwindow* window, double xpos, double ypos);

namespace yume {
    extern Renderer currentRenderer;

    void setWindowSize(unsigned int width, unsigned int height);

    void initWindow(const std::string& title);

    void updateWindow();

    void toggleFullscreen();

    GLFWwindow* getWindowPointer();

    float getDeltaTime();

    glm::vec2 getGlobalScale();

    bool isWindowOpen();

    void setWindowStatus(bool value);

    void setWindowBackgroundColor(glm::vec3 color);

    void swapBuffersPollEvents();

    void setCursorPosCallback(GLFWcursorposfun func);

    void closeWindow();
}
