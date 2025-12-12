#pragma once

#include "../config/config.h"
#include "../gl_program/gl_program.h"

class Square {
private:
    void textureErrorHandler();
    void render_ownShader() const;
    void render_foregoingShader() const;

    unsigned int VBO{}, VAO{}, EBO{};

    unsigned int tex{};
    const char* texPath;
    unsigned char* texData;
    int nrChannels;

    int texWidth{}, texHeight{};

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

public:
    glm::vec3 position;
    glm::vec2 size;
    GlProgram shader;

    bool enable;

    Square(const std::string& path, glm::vec3 position_value, glm::vec2 size_value);
    ~Square();

    void updateVertices();
    void refresh() const;

    void simpleRender();
    void bindTexture() const;
    void render_getShader(const GlProgram& other_shader) const;
    void rotate(glm::vec3 axis, float rotationSpeed) const;
    void setRotation(glm::vec3 axis, float angle) const;
};