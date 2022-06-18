#pragma once

#include <vector>
#include <array>

#include <GL/glew.h>
#include "../bytes.h"


class VertexBuffer {
public:
    VertexBuffer(size_t size = 1);
    ~VertexBuffer();

    const GLuint Descriptor() const;

    template<typename T>
    void InsertData(const std::vector<T>& data) {
        glBufferData(GL_ARRAY_BUFFER, BytesIn(data), data.data(), GL_STATIC_DRAW);
    }

    template<typename T>
    void InsertData(std::vector<T>&& data) {
        InsertData(data);
    }

    template<typename T, size_t len>
    void InsertData(const std::array<T, len>& data) {
        glBufferData(GL_ARRAY_BUFFER, BytesIn(data), data.data(), GL_STATIC_DRAW);
    }

private:
    size_t size_;
    GLuint descriptor;     // buffer descriptor
};
