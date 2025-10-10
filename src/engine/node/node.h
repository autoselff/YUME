#pragma once

#include "../config/config.h"
#include "../node_packages/node_pcg.h"

class Node {
private:

public:
    std::vector<NodePackage> packages {};

	Node(std::vector<NodePackage> node_packages);
	~Node();
};