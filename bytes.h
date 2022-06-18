#pragma once

#include <vector>
#include <array>
#include <cstdint>


template<typename T>
size_t BytesIn(const std::vector<T>& value) {
    return sizeof(T) * value.size();
}

template<typename T, size_t len>
size_t BytesIn(const std::array<T, len>& value) {
    return sizeof(T) * len;
}



