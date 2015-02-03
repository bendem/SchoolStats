#include "data/Data1D.hpp"

Data1D::Data1D(unsigned count, float value) {
    this->count = count;
    this->value = value;
}

Data1D::Data1D(const Data1D& p) {
    this->count = p.count;
    this->value = p.value;
}

Data1D& Data1D::operator=(const Data1D& p) {
    this->count = p.count;
    this->value = p.value;
    return *this;
}
