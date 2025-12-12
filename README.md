# YUME
YUME is an open-source, multiplatform framework for creating 2D games with 3D efects, written from scratch in C++ using OpenGL. The goal of the project is to explore graphic programming and create an excellent tool for people who value simplicity and creating unique computer games.<br>

---
# Docs

## Setup
To start working with YUME, you need to copy the repository to your chosen location. For the purposes of this documentation, let's assume it will be a folder named YUME. Once this is done, you need to download the dependencies required for the framework to work properly: glfw, glm, and deps. Everything is available for download at the link below, which will automatically start the installation of compressed dependencies after clicking. Once they are downloaded, you need to unpack them and place them in the YUME project folder so that everything looks like the diagram below.<br>

**Packages (GLFW, GLM, DEPS (GLAD, STB, KHR))**: [Download Packages](https://github.com/autoselff/autoselff/releases/download/v0.9.2/YUME-packages.zip)

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
├── game_scene.cpp<br>
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
