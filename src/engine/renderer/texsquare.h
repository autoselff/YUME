#pragma once

#include "../config/config.h"
#include "../gl_program/gl_program.h"
#include "../core/window.h"

class Node;

class TexSquare {
public:
    glm::vec3 color{ 0.0f };
    glm::vec2 size{ 1.0f };

    Node* owner{ nullptr };
    GlProgram shader;

    TexSquare(Node* owner, const std::string& path, const glm::vec3& color, const glm::vec2& size);
    ~TexSquare();

    void updateVertices();
    void refresh() const;

    void simpleRender();
    void bindTexture() const;
    void renderWithShader(const GlProgram& otherShader) const;

    void rotate(const glm::vec3& axis, float rotationSpeed) const;
    void setRotation(const glm::vec3& axis, float angle) const;

private:
    GLuint VBO{}, VAO{}, EBO{};
    GLuint texture{};
    int texWidth{}, texHeight{}, nrChannels{};
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    glm::vec3 prevPosition{};
    void loadTexture(const std::string& path);
    void initBuffers();
};