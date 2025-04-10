#include "engine/config/config.h"
#include "engine/config/essentials.h"

int main() {
    yume::setWindowSize(720, 720);
    yume::initWindow("YUME");

	Triangle* triangle = new Triangle({ 0.2f, 0.0f, 1.0f }, { 0.3f, 0.3f });

    GlProgram gl_program;
	gl_program.makeProgramFromPaths("../res/vertex.glsl", "../res/fragment.glsl");

    glEnable(GL_DEPTH_TEST);

    while(yume::isWindowOpen()) {
        yume::updateWindow();

		if (yume::keyPressed(KEY_ESCAPE)) {
			yume::setWindowStatus(false);
		}

		yume::updateInput(yume::getWindowPointer());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(0.4f, 0.2f, 0.3f, 1.0f);

		triangle->simpleRender();

        yume::swapBuffersPollEvents();
    }

    yume::closeWindow();
    delete triangle;
}