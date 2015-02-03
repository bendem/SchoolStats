#ifndef DATA1D_HPP
#define DATA1D_HPP

#include "data/Data.hpp"

class Data1D : public Data {

private:
    unsigned count;
    float value;

public:
    Data1D(unsigned, float);
    Data1D(const Data1D&);

    Data1D& operator=(const Data1D&);

};

#endif
