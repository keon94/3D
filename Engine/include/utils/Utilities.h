#pragma once

namespace utils {

    template <typename T>
    struct array {
        T* data;
        const unsigned int size;
    };

}