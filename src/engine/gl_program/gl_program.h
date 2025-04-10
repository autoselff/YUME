#pragma once

#include "shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>

class GlProgram {
private:
    GLuint id{};
    char countVShaders{};
    std::vector<Shader*> shaders;

public:
    GlProgram();

    GlProgram(Shader* vertexShader, Shader* fragmentShader);
    ~GlProgram();

    void makeProgramFromPaths(const std::string& vertexPath, const std::string& fragmentPath);

    Shader* vShaderPointer(size_t index) const;
    Shader* fShaderPointer(size_t index) const;

    void attachVShader(Shader* vertexShader);
    void attachFShader(Shader* fragmentShader);
    void detachVShader(Shader* vertexShader);
    void detachFShader(Shader* fragmentShader);
    void detachVShader(size_t index);
    void detachFShader(size_t index);

    void linkProgram();

    GLint getId() const;
    void use() const;

    GLint getUniformLocation(const std::string& name);

    void setBool(const std::string& name, bool value) const;
    void setBool(GLint location, bool value) const;

    void setInt(const std::string& name, int value) const;
    void setInt(GLint location, int value) const;

    void setFloat(const std::string& name, float value) const;
    void setFloat(GLint location, float value) const;

    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setVec2(GLint location, const glm::vec2& value) const;
    void setVec2(GLint location, float x, float y) const;

    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec3(GLint location, const glm::vec3& value) const;
    void setVec3(GLint location, float x, float y, float z) const;

    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    void setVec4(GLint location, const glm::vec4& value) const;
    void setVec4(GLint location, float x, float y, float z, float w) const;

    void setMat2(const std::string& name, const glm::mat2& mat) const;
    void setMat2(GLint location, const glm::mat2& mat) const;

    void setMat3(const std::string& name, const glm::mat3& mat) const;
    void setMat3(GLint location, const glm::mat3& mat) const;

    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setMat4(GLint location, const glm::mat4& mat) const;

    void checkLinkingErrors();
};
