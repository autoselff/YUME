#include "node.h"

Node::Node(const glm::vec3& position)
    : position(position)
{

}

Node::~Node() {
    delete texsquare;
}