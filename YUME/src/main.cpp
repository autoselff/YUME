#include "engine/core/window.h"
#include "engine/input/input.h"
#include "engine/config/config.h"

int main() {
    yume::setWindowSize(1280, 720);
    yume::initWindow("YUME");

    glEnable(GL_DEPTH_TEST);

    while(yume::isWindowOpen()) {
        yume::updateWindow();


        if (yume::keyPressed(KEY_ESCAPE))
        {
            yume::setWindowStatus(false);
        }

		yume::updateInput();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        yume::swapBuffersPollEvents();
    }

    yume::closeWindow();
}