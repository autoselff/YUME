# YUME

YUME is a multi-platform open-source game engine written from scratch in C++ using OpenGL. The goal of the project is to explore graphics programming and create a lightweight 2D game engine. 

Currently, work on YUME has slowed down considerably due to the game I am developing and the lack of collaborators. The current version of the engine in this repository is being rewritten to achieve a more transparent architecture and better modularity. This is the reason for the lack of many features and capabilities that the engine recently had. However, it guarantees that the things that are already here are implemented in a much better and more optimal form than they were until recently.

### Latest Version

The latest version of YUME is **0.0.2**, which introduces:
- Easy window mode switching
- Scaling of objects such as `TexSquare` to ensure that textures do not lose their scale and properties regardless of the resolution.
---

### Resources

- **Website**: [YUME Website](https://autoselff.com/games/yume.html)
- **Packages (GLM, GLFW, STB, GLAD...)**: [Download Packages](https://github.com/autoselff/autoselff/releases/download/v0.9.2/YUME-packages.zip)
- **Examples**: [YUME Examples](https://github.com/autoselff/YUME/tree/main/examples)

---

### Lib Structure
YUME<br>
├── src<br>
│   ├── main.cpp<br>
│   ├── engine<br>
│   └── deps<br>
├── res<br>
├── glm<br>
└── glfw<br>
4. 2D Collider Component
5. 2D Collisions
6. 2D Camera
