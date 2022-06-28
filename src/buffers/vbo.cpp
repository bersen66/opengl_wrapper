#include "vbo.h"

VertexBuffer::VertexBuffer(size_t size) : size_(size) {
    glGenBuffers(size_, &descriptor);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(size_, &descriptor); }

const GLuint VertexBuffer::Descriptor() const { return descriptor; }
