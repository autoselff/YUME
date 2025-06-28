#include "gl_program.h"

GlProgram::GlProgram() : id(glCreateProgram()) {
    std::cout << "program nr.: " << id << " has been created." << std::endl;
};

GlProgram::GlProgram(Shader* vertexShader, Shader* fragmentShader) : id(glCreateProgram()) {

    std::cout << "program nr.: " << id << " has been created." << std::endl;

    if (vertexShader->sType() != GL_VERTEX_SHADER || fragmentShader->sType() != GL_FRAGMENT_SHADER)
        std::cout << "ERROR: INCORRECT ARGUMENTS FOR GlProgram CONSTRUCTOR " << std::endl;

    attachVShader(vertexShader);
    attachFShader(fragmentShader);

    linkProgram();
}

// FUNCTIONS

/// <summary>
///To be used on a compleately untouched GlProgram created with the parameterless constuctor.
///Reads shader code from files, compiles it, REPLACES(NOT DELETEs) shader pointers with new objects, 
///attaches shaders to the program, links program, deletes pointers, that is shader objects.
///Mainly for simple useage.
/// </summary>
void GlProgram::makeProgramFromPaths(const std::string& vertexPath, const std::string& fragmentPath) {
    Shader vertexShader = generateShaderPath(GL_VERTEX_SHADER, vertexPath);
    Shader fragmentShader = generateShaderPath(GL_FRAGMENT_SHADER, fragmentPath);

    glAttachShader(id, vertexShader.getId());
    glAttachShader(id, fragmentShader.getId());

    glLinkProgram(id);
    checkLinkingErrors();

    glDeleteShader(vertexShader.getId());
    glDeleteShader(fragmentShader.getId());

    GLint loc = glGetUniformLocation(id, "uTexture");
    std::cerr << "[DEBUG] uTexture location after link: " << loc << "\n";
}


Shader* GlProgram::vShaderPointer(size_t index) const {
    if (index < 0 || index >= countVShaders) {
        std::cout << "WARNING: WRONG VSHADER RETURN INDEX " << std::endl;
        return nullptr;
    }

    return shaders[index];
}
Shader* GlProgram::fShaderPointer(size_t index) const {
    if (index >= shaders.size() || index < countVShaders) {
        std::cout << "WARNING: WRONG FSHADER RFETURN INDEX " << std::endl;
        return nullptr;
    }

    return shaders[index];
}

void GlProgram::attachVShader(Shader* vertexShader) {
    if (vertexShader->sType() != GL_VERTEX_SHADER) {
        std::cout << "ERROR: INCORRECT ARGUMENT FOR attachVShader " << std::endl;
        return;
    }

    shaders.insert(shaders.begin() + countVShaders, vertexShader);
    countVShaders++;
    glAttachShader(id, vertexShader->getId());
}

void GlProgram::attachFShader(Shader* fragmentShader) {
    if (fragmentShader->sType() != GL_FRAGMENT_SHADER) {
        std::cout << "ERROR: INCORRECT ARGUMENT FOR attachFShader " << std::endl;
        return;
    }

    shaders.push_back(fragmentShader);
    glAttachShader(id, fragmentShader->getId());
}

void GlProgram::detachVShader(Shader* vertexShader) {
    if (vertexShader->sType() != GL_VERTEX_SHADER) {
        std::cout << "ERROR: INCORRECT ARGUMENT FOR detachVShader " << std::endl;
        return;
    }

    short i = countVShaders - 1;

    while (i >= 0 && vertexShader != shaders[i]) {
        i--;
    }

    if (i == -1) {
        std::cout << "WARNING: WRONG VSHADER DETACHMENT POINTER " << std::endl;
        return;
    }

    detachVShader(i);
}

void GlProgram::detachFShader(Shader* fragmentShader) {
    if (fragmentShader->sType() != GL_FRAGMENT_SHADER) {
        std::cout << "ERROR: INCORRECT ARGUMENT FOR detachFShader " << std::endl;
        return;
    }

    int i = static_cast<int>(shaders.size()) - 1;
    while (i >= static_cast<int>(countVShaders) && fragmentShader != shaders[i]) {
        i--;
    }
    if (i < static_cast<int>(countVShaders)) {
        std::cout << "WARNING: WRONG FSHADER DETACHMENT POINTER " << std::endl;
        return;
    }

    detachFShader(i);
}

void GlProgram::detachVShader(size_t index) {
    if (index < 0 || index >= countVShaders) {
        std::cout << "WARNING: WRONG VSHADER DETACHMENT INDEX " << std::endl;
        return;
    }

    glDetachShader(id, shaders[index]->getId());
    shaders.erase(shaders.begin() + index);
    countVShaders--;
}

void GlProgram::detachFShader(size_t index) {
    if (index >= shaders.size() || index < countVShaders) {
        std::cout << "WARNING: WRONG FSHADER DETACHMENT INDEX " << std::endl;
        return;
    }

    glDetachShader(id, shaders[index]->getId());
    shaders.erase(shaders.begin() + index);
}

void GlProgram::linkProgram() {
    glLinkProgram(id);
    checkLinkingErrors();
}

GLint GlProgram::getId() const {
    return id;
}

void GlProgram::use() const {
    glUseProgram(id);
}

GLint GlProgram::getUniformLocation(const std::string& name) {
    return glGetUniformLocation(id, name.c_str());
}

void GlProgram::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void GlProgram::setBool(GLint location, bool value) const {
    glUniform1i(location, (int)value);
}

void GlProgram::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void GlProgram::setInt(GLint location, int value) const {
    glUniform1i(location, value);
}

void GlProgram::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void GlProgram::setFloat(GLint location, float value) const {
    glUniform1f(location, value);
}

void GlProgram::setVec2(const std::string& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void GlProgram::setVec2(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}

void GlProgram::setVec2(GLint location, const glm::vec2& value) const {
    glUniform2fv(location, 1, &value[0]);
}
void GlProgram::setVec2(GLint location, float x, float y) const {
    glUniform2f(location, x, y);
}

void GlProgram::setVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void GlProgram::setVec3(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void GlProgram::setVec3(GLint location, const glm::vec3& value) const {
    glUniform3fv(location, 1, &value[0]);
}
void GlProgram::setVec3(GLint location, float x, float y, float z) const {
    glUniform3f(location, x, y, z);
}

void GlProgram::setVec4(const std::string& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void GlProgram::setVec4(const std::string& name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

void GlProgram::setVec4(GLint location, const glm::vec4& value) const {
    glUniform4fv(location, 1, &value[0]);
}
void GlProgram::setVec4(GLint location, float x, float y, float z, float w) const {
    glUniform4f(location, x, y, z, w);
}

void GlProgram::setMat2(const std::string& name, const glm::mat2& mat) const {
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GlProgram::setMat2(GLint location, const glm::mat2& mat) const {
    glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]);
}


void GlProgram::setMat3(const std::string& name, const glm::mat3& mat) const {
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GlProgram::setMat3(GLint location, const glm::mat3& mat) const {
    glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
}


void GlProgram::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GlProgram::setMat4(GLint location, const glm::mat4& mat) const {
    glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}

void GlProgram::checkLinkingErrors() {
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, nullptr, infoLog);
		std::cout << "ERROR: PROGRAM LINKING FAILURE\n" << infoLog << std::endl;
	}
	else {
		std::cout << "PROGRAM LINKING SUCCESS" << std::endl;
	}
}

GlProgram::~GlProgram() {
    glDeleteProgram(id);
    std::cout << "program nr.: " << id << " has been deleted." << std::endl;
}