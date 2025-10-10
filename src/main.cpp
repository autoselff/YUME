#include "engine/config/config.h"
#include "engine/config/essentials.h"


void handle_movement(TexSquare* cat, float speed);

int main() {
    yume::initWindow("YUME");
    yume::runAssistant();

    Node* my_node{ nullptr };
    my_node = new Node({});

    TexSquare* cat{ nullptr };
    cat = new TexSquare("res/textures/cat-bg.png", {0.0f, 0.0f, 0.0f}, COLOR_BLACK, {0.1f, 0.1f});
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
        
        handle_movement(cat, 0.005f);

		yume::updateInput(yume::getWindowPointer());
        yume::setWindowBackgroundColor(COLOR_PURPLE);
        
        cat->rotate({ 0.0f, 1.0f, 0.0f }, 2.6f);
        cat->simpleRender();

        yume::swapBuffersPollEvents();
    }

	delete cat;

    yume::closeWindow();
}

void handle_movement(TexSquare* cat, float speed) {
    if (yume::keyDown(KEY_W)) {
        cat->position += glm::vec3(0.0f, speed, 0.0f);
    }
    else if (yume::keyDown(KEY_S)) {
        cat->position += glm::vec3(0.0f, -speed, 0.0f);
    }

    if (yume::keyDown(KEY_A)) {
        cat->position += glm::vec3(-speed, 0.0f, 0.0f);
    }
    else if (yume::keyDown(KEY_D)) {
        cat->position += glm::vec3(speed, 0.0f, 0.0f);
    }
}