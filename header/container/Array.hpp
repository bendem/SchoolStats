#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <algorithm>

template<class T, unsigned S>
class Array {
private:
    T array[S];

public:
    Array() {}
    Array(const Array<T, S>&);

    unsigned size() const;
    bool empty() const;
    void fill(const T&);

    T& operator[](unsigned i);
    const T& operator[](unsigned i) const;
    Array<T, S>& operator=(Array<T, S>);

};

template<class T, unsigned S>
Array<T, S>::Array(const Array<T, S>& p) {
    for(unsigned i = 0; i < S; ++i) {
        this->array[i] = p.array[i];
    }
}

template<class T, unsigned S>
inline unsigned Array<T, S>::size() const {
    return S;
}

template<class T, unsigned S>
inline bool Array<T, S>::empty() const {
    return S == 0;
}

template<class T, unsigned S>
inline void Array<T, S>::fill(const T& p) {
    std::fill(this->array, this->array + S, p);
}

template<class T, unsigned S>
inline T& Array<T, S>::operator[](unsigned i) {
    return this->array[i];
}

template<class T, unsigned S>
inline const T& Array<T, S>::operator[](unsigned i) const {
    return this->array[i];
}

template<class T, unsigned S>
Array<T, S>& Array<T, S>::operator=(Array<T, S> p) {
    std::swap(this->array, p.array);
    return *this;
}

#endif
