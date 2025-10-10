#include "engine/config/config.h"
#include "engine/config/essentials.h"


void handle_movement(TexSquare* obj, float speed);

int main() {
    yume::initWindow("YUME");
    yume::runAssistant();

    Node* node = new Node({0.0f, 0.0f, 0.0f});
    node->texsquare = new TexSquare("res/textures/cat-bg.png", {0.0f, 0.0f, 0.0f}, COLOR_BLACK, {0.1f, 0.1f});

    node->texsquare->shader.makeProgramFromPaths("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
    node->texsquare->setRotation({ 0.0f, 0.0f, 1.0f}, 90.0f);

    glEnable(GL_DEPTH_TEST);

    while(yume::isWindowOpen()) {
        yume::updateWindow();

		if (yume::keyPressed(KEY_ESCAPE)) {
			yume::setWindowStatus(false);
		}
        if (yume::keyPressed(KEY_F)) {
            yume::toggleFullscreen();
        }
        
        handle_movement(node->texsquare, 0.005f);

		yume::updateInput(yume::getWindowPointer());
        yume::setWindowBackgroundColor(COLOR_PURPLE);
        
        node->texsquare->rotate({ 0.0f, 1.0f, 0.0f }, 2.6f);
        node->texsquare->simpleRender();

        yume::swapBuffersPollEvents();
    }

    delete node;
    yume::closeWindow();
}

void handle_movement(TexSquare* obj, float speed) {
    if (yume::keyDown(KEY_W)) {
        obj->position += glm::vec3(0.0f, speed, 0.0f);
    }
    else if (yume::keyDown(KEY_S)) {
        obj->position += glm::vec3(0.0f, -speed, 0.0f);
    }

    if (yume::keyDown(KEY_A)) {
        obj->position += glm::vec3(-speed, 0.0f, 0.0f);
    }
    else if (yume::keyDown(KEY_D)) {
        obj->position += glm::vec3(speed, 0.0f, 0.0f);
    }
}