#pragma once

#include "../config/config.h"
#include "../gl_program/gl_program.h"

class Triangle {
private:
	unsigned int VBO, VAO, EBO;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

public:
	glm::vec3 position;
	glm::vec2 size;

	bool enable;

	Triangle(glm::vec3 position_value, glm::vec2 size_value);
	~Triangle();

	void updateVertices();
	void refresh() const;

	void simpleRender();
	void render_getShader(const GlProgram& other_shader) const;
	void rotate(glm::vec3 axis, float rotationSpeed) const;
	void setRotation(glm::vec3 axis, float angle) const;	
};