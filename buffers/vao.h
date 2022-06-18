#pragma once

#include <GL/glew.h>

#include "attribute_layout.h"

class VertexArray {
public:
    VertexArray(size_t size = 1);
    ~VertexArray();
    const GLuint Descriptor() const;
    void ApplyAttributeLayout(const AttributeLayout& layout);
private:
    GLuint descriptor; // vertex array descriptor
    size_t attributes_number;
};