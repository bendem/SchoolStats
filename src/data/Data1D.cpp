#include "data/Data1D.hpp"

Data1D::Data1D(unsigned count, float value) {
    this->count = count;
    this->value = value;
}

Data1D::Data1D(const Data1D& p) {
    this->count = p.count;
    this->value = p.value;
}

Data1D& Data1D::add(unsigned count) {
    this->count += count;
    return *this;
}

inline unsigned Data1D::getCount() const {
    return this->count;
}

inline float Data1D::getValue() const {
    return this->value;
}

int Data1D::compareTo(const Data1D& p) const {
    if(this->value == p.value) {
        return 0;
    }
    return this->value > p.value ? 1 : -1;
}

Data1D& Data1D::operator=(const Data1D& p) {
    this->count = p.count;
    this->value = p.value;
    return *this;
}
