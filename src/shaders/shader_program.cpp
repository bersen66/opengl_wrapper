#include "shader_program.h"

#include <GL/glew.h>

#include <iostream>
#include <optional>

ShaderProgram::ShaderProgram() : program_ds(glCreateProgram()) {}

ShaderProgram::~ShaderProgram() {
    glDetachShader(Descriptor(), FSDescriptor());
    glDetachShader(Descriptor(), VSDescriptor());
    glDeleteProgram(Descriptor());
}

const GLuint ShaderProgram::Descriptor() const { return program_ds; }

const GLuint ShaderProgram::VSDescriptor() const { return vertex_shader_ds; }

const GLuint ShaderProgram::FSDescriptor() const { return fragment_shader_ds; }

ShaderProgram& ShaderProgram::SetUniform(const std::string& name, float value) {
    glUniform1f(GetUniformLocation(name), value);
    return *this;
}

ShaderProgram& ShaderProgram::SetUniform(const std::string& name,
                                         const glm::vec2 value) {
    glUniform2f(GetUniformLocation(name), value.x, value.y);
    return *this;
}

ShaderProgram& ShaderProgram::SetUniform(const std::string& name,
                                         const glm::vec3 value) {
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
    return *this;
}

ShaderProgram& ShaderProgram::SetUniform(const std::string& name,
                                         const glm::vec4 value) {
    glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
    return *this;
}

ShaderProgram& ShaderProgram::SetUniform(const std::string& name,
                                         const glm::mat2& value,
                                         bool transpose) {
    glUniformMatrix2fv(GetUniformLocation(name), 1, transpose, &value[0][0]);
    return *this;
}

ShaderProgram& ShaderProgram::SetUniform(const std::string& name,
                                         const glm::mat3& value,
                                         bool transpose) {
    glUniformMatrix3fv(GetUniformLocation(name), 1, transpose, &value[0][0]);
    return *this;
}

ShaderProgram& ShaderProgram::SetUniform(const std::string& name,
                                         const glm::mat4& value,
                                         bool transpose) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, transpose, &value[0][0]);
    return *this;
}

ShaderProgram& ShaderProgram::SetUniform(const std::string& name, int value) {
    glUniform1i(GetUniformLocation(name), value);
    return *this;
}

ShaderProgram& ShaderProgram::SetUniform(const std::string& name,
                                         const glm::ivec2 value) {
    glUniform2i(GetUniformLocation(name), value.x, value.y);
    return *this;
}

ShaderProgram& ShaderProgram::SetUniform(const std::string& name,
                                         const glm::ivec3 value) {
    glUniform3i(GetUniformLocation(name), value.x, value.y, value.z);
    return *this;
}

ShaderProgram& ShaderProgram::SetUniform(const std::string& name,
                                         const glm::ivec4 value) {
    glUniform4i(GetUniformLocation(name), value.x, value.y, value.z, value.w);
    return *this;
}

void ShaderProgram::LoadUniforms() {
    int number_of_active_uniforms = GetNumberOfActiveUniforms();
    for (int location = 0; location < number_of_active_uniforms; location++) {
        uniforms[GetUniformName(location)] = location;
    }
}

int ShaderProgram::GetUniformLocation(const std::string& name) const {
    return uniforms.at(name);
}

std::string ShaderProgram::GetUniformName(int location) const {
    char buffer[32];

    GLsizei length;
    GLint size;
    GLenum type;

    glGetActiveUniform(Descriptor(), (GLuint)location, sizeof(buffer), &length,
                       &size, &type, buffer);
    return {buffer};
}

int ShaderProgram::GetNumberOfActiveUniforms() const {
    int number_of_active_uniforms;
    glGetProgramiv(Descriptor(), GL_ACTIVE_UNIFORMS,
                   &number_of_active_uniforms);
    return number_of_active_uniforms;
}

void ShaderProgram::Link() {
    glLinkProgram(Descriptor());
    glValidateProgram(Descriptor());
    LoadUniforms();
}

bool ShaderProgram::IsValid() const {
    GLint program_linked;
    glGetProgramiv(Descriptor(), GL_LINK_STATUS, &program_linked);
    return program_linked == GL_TRUE;
}

std::string ShaderProgram::GetErrorMessage() const {
    GLsizei log_length = 0;
    char log_message[1024];
    glGetProgramInfoLog(Descriptor(), 1024, &log_length, log_message);
    return log_message;
}

void ShaderProgram::PrintInfoLog(std::ostream& log_stream) const {
    if (IsValid()) {
        log_stream << "PROGRAM LINKING FAILED! LOG:\n"
                   << GetErrorMessage() << std::endl;
        return;
    }
    log_stream << "LINKED SUCCESSFULLY!" << std::endl;
}

void LinkProgram(const ShaderProgram& program, std::ostream& log_stream) {
    // linking
    glLinkProgram(program.Descriptor());
    glValidateProgram(program.Descriptor());

    // checking for errors
    GLint program_linked;
    glGetProgramiv(program.Descriptor(), GL_LINK_STATUS, &program_linked);

    if (program_linked != GL_TRUE) {
        GLsizei log_length = 0;
        GLchar log_message[1024];
        glGetProgramInfoLog(program.Descriptor(), 1024, &log_length,
                            log_message);

        log_stream << "PROGRAM LINKING FAILED! LOG:\n"
                   << log_message << std::endl;
        return;
    }

    log_stream << "LINKED SUCCESSFULLY!" << std::endl;
}

ShaderProgram MakeProgram(const Shader<ShaderType::VERTEX>& vertex_shader,
                          const Shader<ShaderType::FRAGMENT>& fragment_shader) {
    ShaderProgram result;

    CompileShader(vertex_shader);
    CompileShader(fragment_shader);

    result.AttachShader(vertex_shader);
    result.AttachShader(fragment_shader);

    result.Link();

    return result;
}
