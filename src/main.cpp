#include "engine/config/config.h"
#include "engine/config/essentials.h"

// Forward declaration of the node movement handling function
void handle_movement(Node* node, float speed);

/**
 * @brief Main application function for YUME engine
 * 
 * Initializes the engine window, creates a node with a textured square,
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
    
    // Initialize textured square with cat texture and 0.1 x 0.1 scale
    node->initTexSquare("res/textures/cat-bg.png", COLOR_BLACK, {0.1f, 0.1f});

    // Configure shader and add object to renderer
    if (node->texsquare) {
        // Compile and link vertex and fragment shaders
        node->texsquare->shader.makeProgramFromPaths("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
        
        // Set initial rotation of 90 degrees around Z axis
        node->texsquare->setRotation({0.0f, 0.0f, 1.0f}, 90.0f);
        
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
        
        // Handle object movement using arrow keys
        handle_movement(node.get(), 0.005f);

        // Update input state (keyboard, mouse)
        yume::updateInput(yume::getWindowPointer());
        
        // Set background color to purple
        yume::setWindowBackgroundColor(COLOR_PURPLE);
        
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

/**
 * @brief Handles node movement based on pressed arrow keys
 * 
 * This function checks the state of directional keys and modifies
 * the node's position in 2D space (X and Y axes) accordingly. Movement
 * speed is controlled by the speed parameter.
 * 
 * @param node Pointer to the node whose position will be modified
 * @param speed Movement speed (units per frame)
 * 
 * @note Uses keyDown() for continuous movement while key is held
 * @note The if-else structure for opposite directions prevents simultaneous
 *       movement in opposite directions on the same axis
 */
void handle_movement(Node* node, float speed) {
    // Pointer validation - protection against nullptr
    if (!node) return;

    // Vertical movement - up/down (Y axis)
    if (yume::keyDown(KEY_UP)) {
        node->position += glm::vec3(0.0f, speed, 0.0f);
    }
    else if (yume::keyDown(KEY_DOWN)) {
        node->position += glm::vec3(0.0f, -speed, 0.0f);
    }
    
    // Horizontal movement - left/right (X axis)
    if (yume::keyDown(KEY_LEFT)) {
        node->position += glm::vec3(-speed, 0.0f, 0.0f);
    }
    else if (yume::keyDown(KEY_RIGHT)) {
        node->position += glm::vec3(speed, 0.0f, 0.0f);
    }
}