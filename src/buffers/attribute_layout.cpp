#include "attribute_layout.h"

AttributeLayout& AttributeLayout::SetAttribType(GLenum value) {
    attrib_type = value;
    return *this;
}

AttributeLayout& AttributeLayout::SetAttributesNumber(size_t value) {
    size = value;
    return *this;
}

AttributeLayout& AttributeLayout::NeedNormalization(bool value) {
    need_normalization = value;
    return *this;
}

AttributeLayout& AttributeLayout::SetLocationIndex(size_t value) {
    location_index = value;
    return *this;
}

AttributeLayout& AttributeLayout::SetBufferOffset(size_t value) {
    buffer_offset = value;
    return *this;
}

AttributeLayout& AttributeLayout::SetStride(size_t value) {
    stride = value;
    return *this;
}