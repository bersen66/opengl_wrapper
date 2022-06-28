#pragma once

#include <GL/glew.h>

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

// OOP OpenGL shaders wrapper
enum class ShaderType : GLenum {
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER,
};

template <ShaderType type>
class Shader {
public:

    Shader() : shader_ds(glCreateShader(static_cast<GLenum>(type))) {}

    Shader(const std::string& src)
        : shader_ds(glCreateShader(static_cast<GLenum>(type))) {
        SetSource(src);
    }

    Shader(std::string&& src)
        : shader_ds(glCreateShader(static_cast<GLenum>(type))) {
        SetSource(std::move(src));
    }

    ~Shader() { Clear(); }

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader(Shader&& other) = default;

    void SetSource(const std::string& source) {
        const char* content_ptr = source.c_str();
        glShaderSource(Descriptor(), 1, &content_ptr, nullptr);
    }

    void SetSource(std::string&& source) {
        const char* content_ptr = source.c_str();
        glShaderSource(Descriptor(), 1, &content_ptr, nullptr);
    }

    const GLuint Descriptor() const { return shader_ds; }

    ShaderType Type() const { return type; }

private:

    void Clear() { glDeleteShader(Descriptor()); }

private:

    const GLuint shader_ds;  // shaders descriptor
};

template <ShaderType Type>
Shader<Type> LoadShader(std::istream& input) {
    std::string content = {std::istreambuf_iterator<char>(input),
                           std::istreambuf_iterator<char>()};
    return Shader<Type>(std::move(content));
}

template <ShaderType Type>
Shader<Type> LoadShader(const std::string& path) {
    std::ifstream load_file(path);
    Shader<Type> result = LoadShader<Type>(load_file);
    load_file.close();
    return result;
}

template <ShaderType Type>
Shader<Type> LoadShader(std::string&& path) {
    std::ifstream load_file(std::move(path));
    Shader<Type> result = LoadShader<Type>(load_file);
    load_file.close();
    return result;
}

template <ShaderType Type>
Shader<Type> LoadShader(const char* path) {
    std::ifstream load_file(path);
    Shader<Type> result = LoadShader<Type>(load_file);
    load_file.close();
    return result;
}

template <ShaderType Type>
void CompileShader(const Shader<Type>& shader,
                   std::ostream& log_stream = std::cerr) {
    // compilation
    glCompileShader(shader.Descriptor());

    // checking for errors
    GLint shader_compiled;
    glGetShaderiv(shader.Descriptor(), GL_COMPILE_STATUS, &shader_compiled);

    if (shader_compiled != GL_TRUE) {
        GLsizei log_length = 0;
        GLchar log_message[1024];
        glGetShaderInfoLog(shader.Descriptor(), 1024, &log_length, log_message);

        if (Type == ShaderType::VERTEX)
            log_stream << "VERTEX-SHADER COMPILATION FAILED! LOG:\n"
                       << log_message << std::endl;
        else
            log_stream << "FRAGMENT-SHADER COMPILATION FAILED! LOG:\n"
                       << log_message << std::endl;
        return;
    }

    log_stream << (Type == ShaderType::VERTEX ? "VERTEX-" : "FRAGMENT-")
               << "SHADER COMPILED SUCCESSFULLY!" << std::endl;
}