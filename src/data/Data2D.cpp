#include "data/Data2D.hpp"

Data2D::Data2D(float value1, float value2) {
    this->value1 = value1;
    this->value2 = value2;
}

Data2D::Data2D(const Data2D& p) : Data() {
    this->value1 = p.value1;
    this->value2 = p.value2;
}

Data2D& Data2D::operator=(const Data2D& p) {
    this->value1 = p.value1;
    this->value2 = p.value2;
    return *this;
}
