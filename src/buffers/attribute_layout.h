#pragma once
#include "GL/glew.h"

struct AttributeLayout {
    AttributeLayout& SetAttribType(GLenum value);
    AttributeLayout& SetAttributesNumber(size_t value);
    AttributeLayout& NeedNormalization(bool value);
    AttributeLayout& SetLocationIndex(size_t value);
    AttributeLayout& SetBufferOffset(size_t value);
    AttributeLayout& SetStride(size_t value);

    size_t location_index;
    GLenum attrib_type;
    size_t size;
    bool need_normalization;
    size_t buffer_offset;
    size_t stride;
};
