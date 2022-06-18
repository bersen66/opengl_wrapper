#pragma once

#include <optional>
#include <unordered_map>

#include <GL/glew.h>
#include <glm/glm.hpp>


#include "shader.h"


class ShaderProgram {
public:

    ShaderProgram();
    ~ShaderProgram();

    ShaderProgram(ShaderProgram&& other) = default;
    ShaderProgram& operator=(const ShaderProgram& other) = delete;
    ShaderProgram(const ShaderProgram& other) = delete;

    template <ShaderType Type>
    void AttachShader(const Shader<Type>& shader) {
        SetShaderDescriptor(shader);
        glAttachShader(Descriptor(), shader.Descriptor());
    }

    template<ShaderType Type>
    void AttachShader(Shader<Type>&& shader) {
        AttachShader(shader);
    }


    template<ShaderType Type>
    void DetachShader(const Shader<Type>& shader) {
        glDetachShader(Descriptor(), shader.Descriptor());
    }

    ShaderProgram& SetUniform(const std::string& name, float value);
    ShaderProgram& SetUniform(const std::string& name, const glm::vec2 value);
    ShaderProgram& SetUniform(const std::string& name, const glm::vec3 value);
    ShaderProgram& SetUniform(const std::string& name, const glm::vec4 value);

    ShaderProgram& SetUniform(const std::string& name, const glm::mat2& value, bool transpose = false);
    ShaderProgram& SetUniform(const std::string& name, const glm::mat3& value, bool transpose = false);
    ShaderProgram& SetUniform(const std::string& name, const glm::mat4& value, bool transpose = false);

    ShaderProgram& SetUniform(const std::string& name, int value);
    ShaderProgram& SetUniform(const std::string& name, const glm::ivec2 value);
    ShaderProgram& SetUniform(const std::string& name, const glm::ivec3 value);
    ShaderProgram& SetUniform(const std::string& name, const glm::ivec4 value);

    const GLuint Descriptor() const;
    const GLuint VSDescriptor() const;
    const GLuint FSDescriptor() const;

    void Link();

    bool IsValid() const;

    std::string GetErrorMessage() const;

    void PrintInfoLog(std::ostream& log_stream = std::cerr) const;
private:

    template<ShaderType Type>
    void SetShaderDescriptor(const Shader<Type>& shader) {
        if (shader.Type() == ShaderType::FRAGMENT) {
            fragment_shader_ds = shader.Descriptor();
        } else {
            vertex_shader_ds = shader.Descriptor();
        }
    }

private:

    void LoadUniforms();

    int GetUniformLocation(const std::string& name) const;

    std::string GetUniformName(int location) const;

    int GetNumberOfActiveUniforms() const;

private:
    using UniformTable = std::unordered_map<std::string, GLint>; // {name, location}
private:
    UniformTable uniforms;
    const GLuint program_ds;       // program descriptor
    GLuint fragment_shader_ds;     // fragment shaders descriptor
    GLuint vertex_shader_ds;       // vertex shaders descriptor
};

//void LinkProgram(const ShaderProgram& program, std::ostream& log_stream = std::cerr);


ShaderProgram MakeProgram (
        const Shader<ShaderType::VERTEX>&   vertex_shader,
        const Shader<ShaderType::FRAGMENT>& fragment_shader
);