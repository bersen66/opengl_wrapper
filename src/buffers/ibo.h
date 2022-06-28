#pragma once

#include <GL/glew.h>

#include <array>
#include <vector>

class IndexBuffer {
public:

    IndexBuffer(size_t size = 1);
    ~IndexBuffer();

    const GLuint Descriptor() const;

    template <typename T>
    void InsertData(const std::vector<T>& data) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, BytesIn(data), data.data(),
                     GL_STATIC_DRAW);
    }

    template <typename T>
    void InsertData(std::vector<T>&& data) {
        InsertData(data);
    }

    template <typename T, size_t len>
    void InsertData(const std::array<T, len>& data) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, BytesIn(data), data.data(),
                     GL_STATIC_DRAW);
    }

private:

    size_t size_;
    GLuint descriptor;  // index buffer descriptor
};