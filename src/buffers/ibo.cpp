#include "ibo.h"

IndexBuffer::IndexBuffer(size_t size) : size_(size) {
    glGenBuffers(size_, &descriptor);
}

const GLuint IndexBuffer::Descriptor() const { return descriptor; }

IndexBuffer::~IndexBuffer() { glDeleteBuffers(size_, &descriptor); }