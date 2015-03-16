#ifndef DATA2D_HPP
#define DATA2D_HPP

#include "data/Data.hpp"

class Data2D : public Data {

private:
    float value1;
    float value2;

public:
    Data2D(float, float);
    Data2D(const Data2D&);

    Data2D& operator=(const Data2D&);

    float getValue1() const;
    float getValue2() const;

    void setValue1(float value1);
    void setValue2(float value2);

};

inline float Data2D::getValue1() const {
    return value1;
}

inline float Data2D::getValue2() const {
    return value2;
}

inline void Data2D::setValue1(float value1) {
    this->value1 = value1;
}

inline void Data2D::setValue2(float value2) {
    this->value2 = value2;
}

#endif
