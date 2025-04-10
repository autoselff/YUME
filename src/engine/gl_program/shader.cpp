#include "shader.h"

const char* names[4] = { "VERTEX", "FRAGMENT", "UNKNOWN", "I TOLD U IT MUST BE GL_VERTEX_SHADER || GL_FRAGMENT_SHADER" };

Shader::Shader(GLenum sType) {
    switch (sType) {
    case GL_VERTEX_SHADER:
        id = glCreateShader(GL_VERTEX_SHADER);
        break;
    case GL_FRAGMENT_SHADER:
        id = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    default:
        id = 0;
    }
    std::cout << sTypeStr() << " shader nr.: " << id << " has been created." << std::endl;
}

const char* Shader::sTypeStr() const {
    return ((sType() == GL_VERTEX_SHADER) ? names[0] : ((sType() == GL_FRAGMENT_SHADER) ? names[1] : ((sType() == 0) ? names[3] : names[2])));
}

GLenum Shader::sType() const {
    GLenum ret{};
    glGetShaderiv(id, GL_SHADER_TYPE, (int*)&ret);
    return ret;
}

GLuint Shader::getId() {
    return id;
}

void Shader::loadShaderPath(const std::string& path) {
    std::ifstream file;
    std::stringstream stream;
    std::string string;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // open file
        file.open(path);

        // read file's buffer contents into streams
        stream << file.rdbuf();

        // close file handler
        file.close();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR: SHADER FILE READ FAILURE : " << e.what() << std::endl;
    }

    string = stream.str();
    loadShaderSource(string.c_str());
}

void Shader::loadShaderSource(const GLchar* shaderSource) {
    glShaderSource(id, 1, &shaderSource, nullptr);
    glCompileShader(id);
    checkCompileErrors();
}

void Shader::checkCompileErrors() {
    GLint success;
    GLchar infoLog[1024];

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(id, 1024, nullptr, infoLog);
        std::cerr << "ERROR: SHADER COMPILATION ERROR ; TYPE: " << sTypeStr() << std::endl
            << infoLog << std::endl << " -- --------------------------------------------------- -- " << std::endl;
    }
}


Shader::~Shader() {
    std::cout << sTypeStr() << " shader nr.: " << id << " has been deleted." << std::endl;
    glDeleteShader(id);
}

Shader generateShaderPath(GLenum sType, const std::string& path) {
    Shader shade = Shader(sType);
    shade.loadShaderPath(path);
    return shade;
}
Shader generateShaderSource(GLenum sType, const char* sourceCode) {
    Shader shade = Shader(sType);
    shade.loadShaderSource(sourceCode);
    return shade;
}