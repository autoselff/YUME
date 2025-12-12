#include "texsquare.h"
#include "../node/node.h"

TexSquare::TexSquare(Node* owner, const std::string& path, const glm::vec3& color, const glm::vec2& size)
    : owner(owner), color(color), size(size)
{
    if (owner) prevPosition = owner->position;

    loadTexture(path);
    initBuffers();
    updateVertices();
    refresh();
}

TexSquare::~TexSquare() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture);
}

void TexSquare::loadTexture(const std::string& path) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(path.c_str(), &texWidth, &texHeight, &nrChannels, 0);
    if (data) {
        GLenum format = nrChannels == 4 ? GL_RGBA : (nrChannels == 3 ? GL_RGB : GL_RED);
        glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "Failed to load texture: " << path << std::endl;
    }
    stbi_image_free(data);
}

void TexSquare::initBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    indices = { 0, 1, 3, 1, 2, 3 };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void TexSquare::updateVertices() {
    glm::vec3 pos = owner ? owner->position : glm::vec3(0.0f);

    float normalizedX = pos.x / yume::WINDOW_WIDTH;
    float normalizedY = pos.y / yume::WINDOW_HEIGHT;

    pos = {normalizedX, normalizedY, pos.z};

    vertices = {
        // top-right
        pos.x + size.x * yume::getGlobalScale().x, 
        pos.y + size.y * yume::getGlobalScale().y, 
        pos.z, color.r, color.g, color.b, 1.0f, 1.0f,

        // bottom-right
        pos.x + size.x * yume::getGlobalScale().x, 
        pos.y - size.y * yume::getGlobalScale().y, 
        pos.z, color.r, color.g, color.b, 1.0f, 0.0f,

        // bottom-left
        pos.x - size.x * yume::getGlobalScale().x, 
        pos.y - size.y * yume::getGlobalScale().y, 
        pos.z, color.r, color.g, color.b, 0.0f, 0.0f,

        // top-left
        pos.x - size.x * yume::getGlobalScale().x, 
        pos.y + size.y * yume::getGlobalScale().y, 
        pos.z, color.r, color.g, color.b, 0.0f, 1.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void TexSquare::refresh() const {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void TexSquare::simpleRender() {
    glBindTexture(GL_TEXTURE_2D, texture);
    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glm::vec3 curPos = owner ? owner->position : glm::vec3(0.0f);
    if (prevPosition != curPos) {
        updateVertices();
        refresh();
        prevPosition = curPos;
    }
}

void TexSquare::bindTexture() const {
    glBindTexture(GL_TEXTURE_2D, texture);
}

void TexSquare::renderWithShader(const GlProgram& otherShader) const {
    otherShader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void TexSquare::rotate(const glm::vec3& axis, float rotationSpeed) const {
    glm::vec3 pos = owner ? owner->position : glm::vec3(0.0f);
    glm::mat4 transform(1.0f);
    transform = glm::translate(transform, pos);
    transform = glm::rotate(transform, -rotationSpeed * (float)glfwGetTime(), axis);
    transform = glm::translate(transform, -pos);

    shader.use();
    shader.setMat4("transform", transform);
}

void TexSquare::setRotation(const glm::vec3& axis, float angle) const {
    glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(-angle), axis);
    shader.use();
    shader.setMat4("transform", transform);
}