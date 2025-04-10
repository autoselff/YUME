#include "triangle.h"

Triangle::Triangle(glm::vec3 position_value, glm::vec2 size_value)
	: position(position_value), size(size_value), enable(true) {
	vertices = {
		position.x + -size.x, position.y + -size.y, 0.0f, // left  
        position.x + size.x, position.y + -size.y, 0.0f, // right 
        position.x, position.y + size.y, 0.0f,  // top   
	};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    std::cout << "The triangle has been successfully created" << std::endl;
}	

void Triangle::simpleRender() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

Triangle::~Triangle() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

    std::cout << "The triangle has been successfully deleted" << std::endl;
}