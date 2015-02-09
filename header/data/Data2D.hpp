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

};

#endif
