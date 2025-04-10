#include "engine/config/config.h"
#include "engine/config/essentials.h"

#include "engine/renderer/square.h"

int main() {
    yume::setWindowSize(720, 720);
    yume::initWindow("YUME");

    Square* square = new Square("C:/Users/mydat/Documents/YUME/res/box.png", { 0.0f, 0.0f, 1.0f }, { 0.2f, 0.2f });
	square->shader.makeProgramFromPaths("C:/Users/mydat/Documents/YUME/res/vertex.glsl", "C:/Users/mydat/Documents/YUME/res/fragment.glsl");

    glEnable(GL_DEPTH_TEST);

    while(yume::isWindowOpen()) {
        yume::updateWindow();

		if (yume::keyPressed(KEY_ESCAPE)) {
			yume::setWindowStatus(false);
		}

		yume::updateInput(yume::getWindowPointer());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		square->simpleRender();

        yume::swapBuffersPollEvents();
    }

    std::cout << "closing....\n";

    yume::closeWindow();
	delete square;
}