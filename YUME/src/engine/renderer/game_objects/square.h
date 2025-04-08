#ifndef YUME_SQUARE_H
#define YUME_SQUARE_H

// YUME ENGINE
#include "../../config/config.h"

// OTHER PACKAGES
#include "../../math/math.h"
#include "../../gl_program/gl_program.h"

class Square {
public:

	yume::vec2yu<float> position{};
	yume::vec2yu<float> size{};
	yume::vec4yu<float> color{};

	GlProgram shader{};

	bool enabled{ true };

	Square(yume::vec2yu<float> position_t, yume::vec2yu<float> size_t, yume::vec4yu<float> color_t);
	~Square();

	void simpleRender() const;
	void advancedRender() const;
	void bindTexture() const;
	void update();


private:
	unsigned int VBO{}, VAO{}, EBO{};
	std::vector<float> vertices;

	void render_ownShader() const;
	void render_foregoingShader() const;
};

#endif