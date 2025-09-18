#pragma once

#include "../config/config.h"

void mouseCallback(GLFWwindow* window, double xpos, double ypos);

namespace yume {

    void setWindowSize(unsigned int width, unsigned int height);

    void initWindow(const std::string& title);

    void updateWindow();

    void toggleFullscreen();

    GLFWwindow* getWindowPointer();

    float getDeltaTime();

    glm::vec2 getGlobalScale();

    bool isWindowOpen();

    void setWindowStatus(bool value);

    void swapBuffersPollEvents();

    void setCursorPosCallback(GLFWcursorposfun func);

    void closeWindow();
}
