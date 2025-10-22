#pragma once

#include "../config/config.h"
#include "../renderer/texsquare.h"

class Node {
public:
    glm::vec3 position{ 0.0f };

    std::unique_ptr<TexSquare> texsquare;

    Node(const glm::vec3& position);
    Node(const glm::vec3& position, const std::string& texPath, const glm::vec3& color, const glm::vec2& size);
    ~Node();

    void initTexSquare(const std::string& texPath, const glm::vec3& color, const glm::vec2& size);
};