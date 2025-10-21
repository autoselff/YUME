#include "node.h"

Node::Node(const glm::vec3& position)
    : position(position), texsquare(nullptr)
{
}

Node::Node(const glm::vec3& position, const std::string& texPath, const glm::vec3& color, const glm::vec2& size)
    : position(position)
{
    texsquare = std::make_unique<TexSquare>(this, texPath, color, size);
}

Node::~Node() {

}

void Node::initTexSquare(const std::string& texPath, const glm::vec3& color, const glm::vec2& size) {
    texsquare = std::make_unique<TexSquare>(this, texPath, color, size);
}