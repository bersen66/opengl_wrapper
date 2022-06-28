#include "vao.h"

VertexArray::VertexArray(size_t size) : attributes_number(size) {
    glGenVertexArrays(size, &descriptor);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(attributes_number, &descriptor);
}

const GLuint VertexArray::Descriptor() const { return descriptor; }

void VertexArray::ApplyAttributeLayout(const AttributeLayout& layout) {
    glEnableVertexAttribArray(layout.location_index);
    glVertexAttribPointer(layout.location_index, layout.size,
                          layout.attrib_type, layout.need_normalization,
                          layout.stride, (const GLvoid*)layout.buffer_offset);
}