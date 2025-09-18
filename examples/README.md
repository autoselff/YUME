### The examples below show the sample content of the main.cpp file. The versions of the YUME engine with which the examples are compatible are listed in the comment at the very top of the example.

main.cpp

```cpp
// 0.0.2 - SPINNING CAT

#include "engine/config/config.h"
#include "engine/config/essentials.h"

int main() {
    yume::initWindow("YUME");
    yume::runAssistant();

    TexSquare* cat{ nullptr };
    cat = new TexSquare("res/textures/cat-bg.png", {0.0f, 0.0f, 0.0f}, { 1.0, 1.0, 1.0 }, {0.5f, 0.5f});
    cat->shader.makeProgramFromPaths("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
    cat->setRotation({ 0.0f, 0.0f, 1.0f}, 90.0f);

    glEnable(GL_DEPTH_TEST);

    while(yume::isWindowOpen()) {
        yume::updateWindow();

		if (yume::keyPressed(KEY_ESCAPE)) {
			yume::setWindowStatus(false);
		}
        if (yume::keyPressed(KEY_F)) {
            yume::toggleFullscreen();
        }

		yume::updateInput(yume::getWindowPointer());
        glClearColor(0.4f, 0.2f, 0.3f, 1.0f);
        
        cat->rotate({ 0.0f, 1.0f, 0.0f }, 2.6f);
        cat->simpleRender();

        yume::swapBuffersPollEvents();
    }

	delete cat;

    yume::closeWindow();
}

```