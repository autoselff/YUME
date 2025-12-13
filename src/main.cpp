#include "engine/config/config.h"
#include "engine/config/essentials.h"

/**
 * @brief Main application function for YUME engine
 * 
 * @details Initializes the engine window, creates a node with a textured square,
 * configures shaders and rendering, then runs the main game loop
 * with keyboard input handling and object rotation animation.
 * 
 * @return int Application exit code (0 on successful termination)
 */
int main() {
    // Initialize the graphics engine window
    yume::initWindow("YUME");

    // Create a smart pointer to a scene node at initial position (0,0,0)
    auto node = std::make_unique<Node>(glm::vec3{0.0f, 0.0f, 0.0f});
    glm::vec3 velocity{ 0.0f };
    
    // Initialize textured square with cat texture and 0.1 x 0.1 scale
    node->initTexSquare("res/textures/cat-bg.png", COLOR_BLACK, {0.1f, 0.1f});

    // Configure shader and add object to renderer
    if (node->texsquare) {
        // Compile and link vertex and fragment shaders
        node->texsquare->shader.makeProgramFromPaths("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
        
        // Set initial rotation of 90 degrees around Z axis
        node->texsquare->setRotation({0.0f, 0.0f, 0.0f}, 0.0f);
        
        // Register object in the rendering system
        yume::currentRenderer.addToRender(node->texsquare.get());
    }

    // Main game loop - executes while window is open
    while(yume::isWindowOpen()) {
        // Update window state and process system events
        yume::updateWindow();

        // Handle ESC key - close application
        if (yume::keyPressed(KEY_ESCAPE)) {
            yume::setWindowStatus(false);
        }
        
        // Handle F key - toggle fullscreen mode
        if (yume::keyPressed(KEY_F)) {
            yume::toggleFullscreen();
        }
        
        // Update input state (keyboard, mouse)
        yume::updateInput(yume::getWindowPointer());
        
        // Set background color to purple
        yume::setWindowBackgroundColor(COLOR_PURPLE);

        // Handle prototype physics of the node
        node->position += velocity * yume::getDeltaTime();
        velocity += glm::vec3(0.0f, -9.81 * 30.0f, 0.0f) * yume::getDeltaTime();

        if (node->position.y < -500 || node->position.y > yume::WINDOW_HEIGHT) {
            velocity.y *= -0.95f;
        }
        if (node->position.x < -500 || node->position.x > yume::WINDOW_WIDTH) {
            velocity.x *= -0.95f;
        }
        
        // Animation - continuous rotation of object around Y axis
        if (node->texsquare) {
            node->texsquare->rotate({0.0f, 1.0f, 0.0f}, 2.6f);
        }
    }

    // Resource cleanup - release node
    node.reset();
    
    // Close window and release engine resources
    yume::closeWindow();
}