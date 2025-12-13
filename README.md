# YUME
YUME is a cross-platform framework that simplifies the creation of simple 2D games with 3D effects using C++. The goal of the project is to explore graphic programming and create an excellent tool for people who value simplicity and control over the tools they use.<br>

---
# Docs

## Setup
To start working with YUME, you need to copy the repository to your chosen location. For the purposes of this documentation, let's assume it will be a folder named YUME. Once this is done, you need to download the dependencies required for the framework to work properly: glfw, glm, and deps. Everything is available for download at the link below, which will automatically start the installation of compressed dependencies after clicking. Once they are downloaded, you need to unpack them and place them in the YUME project folder so that everything looks like the diagram below.<br>

**Dependencies (GLFW, GLM, DEPS (GLAD, STB, KHR))**: [Download Dependencies](https://github.com/autoselff/YUME/releases/download/v0.1.0/dependencies.zip)

YUME<br>
├── CMakeLists.txt<br>
├── build<br>
├── res<br>
├── src<br>
│   ├── main.cpp<br>
│   └── engine<br>
├── deps<br>
├── glm<br>
└── glfw<br>

### Start
Once the setup has been successfully completed, you can start creating your first program. YUME is designed so that the entire project should be located in the src folder and should not enter the engine folder to avoid accidentally interfering with the framework's structure. For example, below is a sample project structure.<br>

src<br>
├── main.cpp<br>
├── scenes<br>
│   ├── game_scene.cpp<br>
│   ├── game_scene.h<br>
│   ├── menu_scene.cpp<br>
│   └── menu_scene.h<br>
└── engine<br>

It's worth remembering that when creating new files in the project, you should also add them to the CMakeLists.txt located in the main folder, analogously to the rest of the files.<br><br>
All project files such as sample shaders and textures are located in the res folder, and those created later by the user should also be placed there because it is automatically copied to the project build location, which allows you not to worry about paths, etc. If you want to access something, simply write <code>res/folder/file.png</code> from the level of, for example, main.cpp.

### Build

To compile your project and thus the entire framework, since YUME allows direct access and modification of the engine code, you need to create a new folder named, for example, build, preferably in the main folder. Then navigate to it and configure cmake from the terminal with the command  <code>cmake ../</code> then you need to execute the Makefile created by cmake with the command <code>make</code>. When this is done, all that remains is to go to the newly created /out folder and run the project with the command <code>./PROJECT_NAME</code> or from the file manager simply click on the project icon.<br><br>
To modify the project name, you need to do it directly from the CMakeLists.txt in the main folder by replacing YUME in the second line with any other name.

---

## First program
### Main loop
To create your first program, you need to go to the main.cpp file, which will always be the core of the entire program. Once you've done that, you need to include the necessary YUME framework modules. Currently, they are divided into just two modules, and we'll need both of them.
```cpp
#include "engine/config/config.h"
#include "engine/config/essentials.h"
```

Next, you need to create your main function, which is the beginning and end of everything that will happen.
```cpp
int main() {
    // Initialize the graphics engine window
    yume::initWindow("YUME");
    
    // Main game loop - executes while window is open
    while(yume::isWindowOpen()) {
        // Update window state and process system events
        yume::updateWindow();
        
        // Handle ESC key - close application
        if (yume::keyPressed(KEY_ESCAPE)) {
            yume::setWindowStatus(false);
        }
    }
    
    // Close window and release engine resources
    yume::closeWindow();
}
```

This creates a basic window that will stay open until you press the ESC key. Now let's expand this program to display something on the screen.

--- 

### First node
In YUME, visual objects are created using Nodes. A Node is a container that can hold various types of renderable objects. Let's create a node with a textured square:

```cpp
int main() {
    yume::initWindow("YUME");

    // Create a smart pointer to a scene node at initial position (0,0,0)
    auto node = std::make_unique<Node>(glm::vec3{0.0f, 0.0f, 0.0f});
    
    // Initialize textured square with cat texture and 0.1 x 0.1 scale
    node->initTexSquare("res/textures/cat-bg.png", COLOR_BLACK, {0.1f, 0.1f});

    // Setting start rotation
    node->texsquare->setRotation({0.0f, 0.0f, 0.0f}, 0.0f);

    // Main game loop
    while(yume::isWindowOpen()) {
        yume::updateWindow();
        
        if (yume::keyPressed(KEY_ESCAPE)) {
            yume::setWindowStatus(false);
        }
    }
    
    // Resource cleanup - release node
    node.reset();
    yume::closeWindow();
}
```

### Configuring shaders and renderer
Shaders are programs that run on the GPU and determine how objects are displayed. YUME requires you to specify vertex and fragment shaders:
```cpp
// Configure shader and add object to renderer
if (node->texsquare) {
    // Compile and link vertex and fragment shaders
    node->texsquare->shader.makeProgramFromPaths("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
    
    // Register object in the rendering system
    yume::currentRenderer.addToRender(node->texsquare.get());
}
```

### Adding Movement 
Let's add keyboard controls to move our object. First, create a function:
```cpp
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
```

Now add this function call to your main loop, along with input updates:
```cpp
while(yume::isWindowOpen()) {
    yume::updateWindow();

    if (yume::keyPressed(KEY_ESCAPE)) {
        yume::setWindowStatus(false);
    }
    
    // Handle object movement using arrow keys
    handle_movement(node.get(), 0.005f);

    // Update input state (keyboard, mouse)
    yume::updateInput(yume::getWindowPointer());
}
```

### Adding rotation and background color
```cpp
while(yume::isWindowOpen()) {
    yume::updateWindow();

    if (yume::keyPressed(KEY_ESCAPE)) {
        yume::setWindowStatus(false);
    }
    
    // Handle F key - toggle fullscreen mode
    if (yume::keyPressed(KEY_F)) {
        yume::toggleFullscreen();
    }
    
    handle_movement(node.get(), 0.005f);
    yume::updateInput(yume::getWindowPointer());
    
    // Set background color to purple
    yume::setWindowBackgroundColor(COLOR_PURPLE);
    
    // Animation - continuous rotation of object around Y axis
    if (node->texsquare) {
        node->texsquare->rotate({0.0f, 1.0f, 0.0f}, 2.6f);
    }
}
```

### Complete Program
```cpp
#include "engine/config/config.h"
#include "engine/config/essentials.h"

void handle_movement(Node* node, float speed);

int main() {
    yume::initWindow("YUME");

    auto node = std::make_unique<Node>(glm::vec3{0.0f, 0.0f, 0.0f});
    node->initTexSquare("res/textures/cat-bg.png", COLOR_BLACK, {0.1f, 0.1f});
    node->texsquare->setRotation({0.0f, 0.0f, 0.0f}, 0.0f);

    if (node->texsquare) {
        node->texsquare->shader.makeProgramFromPaths("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
        yume::currentRenderer.addToRender(node->texsquare.get());
    }

    while(yume::isWindowOpen()) {
        yume::updateWindow();

        if (yume::keyPressed(KEY_ESCAPE)) {
            yume::setWindowStatus(false);
        }
        
        if (yume::keyPressed(KEY_F)) {
            yume::toggleFullscreen();
        }
        
        handle_movement(node.get(), 0.005f);
        yume::updateInput(yume::getWindowPointer());
        yume::setWindowBackgroundColor(COLOR_PURPLE);
        
        if (node->texsquare) {
            node->texsquare->rotate({0.0f, 1.0f, 0.0f}, 2.6f);
        }
    }

    node.reset();
    yume::closeWindow();
}

void handle_movement(Node* node, float speed) {
    if (!node) return;

    if (yume::keyDown(KEY_UP)) {
        node->position += glm::vec3(0.0f, speed, 0.0f);
    }
    else if (yume::keyDown(KEY_DOWN)) {
        node->position += glm::vec3(0.0f, -speed, 0.0f);
    }
    
    if (yume::keyDown(KEY_LEFT)) {
        node->position += glm::vec3(-speed, 0.0f, 0.0f);
    }
    else if (yume::keyDown(KEY_RIGHT)) {
        node->position += glm::vec3(speed, 0.0f, 0.0f);
    }
}
```
