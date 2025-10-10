#pragma once

#include "../config/config.h"
#include "../node_packages/node_pcg.h"
#include "../renderer/texsquare.h"

class Node {
public:
	glm::vec3 position{ 0.0f };

	TexSquare* texsquare{ nullptr };

	Node(const glm::vec3& position);
	~Node();
};