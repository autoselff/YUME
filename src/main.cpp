#include "engine/config/config.h"
#include "engine/config/essentials.h"
#include "engine/config/data.h"

int main() {
    yume::setWindowSize(720, 720);
    yume::initWindow("YUME");

    TexSquare* cat{ nullptr };
    cat = new TexSquare(CAT, {0.0f, 0.0f, 0.0f}, { 1.0, 1.0, 1.0 }, {0.5f, 0.5f});
    cat->shader.makeProgramFromPaths(VERTEX_SHADER, FRAGMENT_SHADER);
    cat->setRotation({ 0.0f, 0.0f, 1.0f}, 90.0f);

    float i = 0.0f;

    glEnable(GL_DEPTH_TEST);

    while(yume::isWindowOpen()) {
        yume::updateWindow();

		if (yume::keyPressed(KEY_ESCAPE)) {
			yume::setWindowStatus(false);
		}

		yume::updateInput(yume::getWindowPointer());
		cat->rotate({ 1.0f, 0.0f, 0.0f }, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(0.4f, 0.2f, 0.3f, 1.0f);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        cat->simpleRender();

        yume::swapBuffersPollEvents();
    }

	delete cat;

    yume::closeWindow();
}