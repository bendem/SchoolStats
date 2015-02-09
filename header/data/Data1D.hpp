#ifndef DATA1D_HPP
#define DATA1D_HPP

#include "data/Data.hpp"
#include "utils/Comparable.hpp"

class Data1D : public Data, public Comparable<Data1D> {

private:
    unsigned count;
    float value;

public:
    Data1D(unsigned, float);
    Data1D(const Data1D&);

    Data1D& add(unsigned);
    unsigned getCount() const;
    float getValue() const;


    int compareTo(const Data1D&) const;

    Data1D& operator=(const Data1D&);

};

#endif
