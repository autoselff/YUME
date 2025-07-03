#include "window.h"
#include <iostream>

namespace yume {
    unsigned int WINDOW_WIDTH{ 720 };
    unsigned int WINDOW_HEIGHT{ 720 };

    float WINDOW_WIDTH_SCALE{};
    float WINDOW_HEIGHT_SCALE{};

    GLFWwindow* _window{ nullptr };

    float last_frame{};
    float delta_time{};

    void setWindowSize(unsigned int width, unsigned int height) {
        WINDOW_WIDTH = width;
        WINDOW_HEIGHT = height;
    }

    void initWindow(const std::string& title) {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        _window = glfwCreateWindow((int)WINDOW_WIDTH, (int)WINDOW_HEIGHT, title.c_str(), nullptr, nullptr);

        WINDOW_WIDTH_SCALE = static_cast<float>(WINDOW_WIDTH) / 720;
        WINDOW_HEIGHT_SCALE = static_cast<float>(WINDOW_HEIGHT) / 720;

        if (_window == nullptr) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        else {
            std::cout << "GLFW window created correctly" << std::endl;
        }

        glfwMakeContextCurrent(_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD\n";
            return;
        }
        else {
            std::cout << "GLAD initialized correctly\n";
            std::cout << "YUME 0.0.1 started\n";
        }

        glfwSwapInterval(1);
        std::cout << std::endl << std::flush;
    }

    void updateWindow() {
        // DELTA TIME
        auto current_frame = static_cast<float>(glfwGetTime());
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        // DEPTH
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ALPHA
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    GLFWwindow* getWindowPointer() {
        return _window;
    }

    float getDeltaTime() {
        return delta_time;
    }

    glm::vec2 getGlobalScale() {
        return {WINDOW_HEIGHT_SCALE, WINDOW_WIDTH_SCALE};
    }

    bool isWindowOpen() {
        return !glfwWindowShouldClose(_window);
    }

    void setWindowStatus(bool value) {
        glfwSetWindowShouldClose(_window, !value);
    }

    void swapBuffersPollEvents() {
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }

    void setCursorPosCallback(GLFWcursorposfun func) {
        glfwSetCursorPosCallback(_window, func);
    }

    void closeWindow() {
        std::cout << "\nclosing....\n\n";

        glfwDestroyWindow(_window);
        glfwTerminate();
    }
}

