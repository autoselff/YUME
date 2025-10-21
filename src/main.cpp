#include "engine/config/config.h"
#include "engine/config/essentials.h"
#include "engine/node/node.h"

void handle_movement(Node* node, float speed);

int main() {
    yume::initWindow("YUME");
    yume::runAssistant();

    Node* node = new Node({0.0f, 0.0f, 0.0f}, "res/textures/cat-bg.png", COLOR_BLACK, {0.1f, 0.1f});
    // Node* node = new Node({0.0f,0.0f,0.0f});
    // node->initTexSquare("res/textures/cat-bg.png", COLOR_BLACK, {0.1f,0.1f});

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
        
        handle_movement(node, 0.005f);

        yume::updateInput(yume::getWindowPointer());
        yume::setWindowBackgroundColor(COLOR_PURPLE);
        
        if (node->texsquare) {
            node->texsquare->rotate({ 0.0f, 1.0f, 0.0f }, 2.6f);
            node->texsquare->simpleRender();
        }

        yume::swapBuffersPollEvents();
    }

    delete node;
    yume::closeWindow();
}

void handle_movement(Node* node, float speed) {
    if (!node) return;

    if (yume::keyDown(KEY_W)) {
        node->position += glm::vec3(0.0f, speed, 0.0f);
    }
    else if (yume::keyDown(KEY_S)) {
        node->position += glm::vec3(0.0f, -speed, 0.0f);
    }

    if (yume::keyDown(KEY_A)) {
        node->position += glm::vec3(-speed, 0.0f, 0.0f);
    }
    else if (yume::keyDown(KEY_D)) {
        node->position += glm::vec3(speed, 0.0f, 0.0f);
    }
}