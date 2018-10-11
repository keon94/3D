#pragma once
#include <assert.h>

template <typename T>
class Matrix2 {

private:

    T m_array[4] = { 0, 0, 0, 0 };

public:

    Matrix2() = default;

    Matrix2(const T row1[2], const T row2[2]) {
        m_array[0] = row1[0];
        m_array[1] = row1[1];
        m_array[2] = row2[0];
        m_array[3] = row2[1];
    }

    T& operator() (const unsigned int i, const unsigned int j) {
        assert(i < 2 && j < 2);
        return m_array[2*i + j];        
    }

    T operator() (const unsigned int i, const unsigned int j) const {
        assert(i < 2 && j < 2);
        return m_array[2*i + j];
    }

};