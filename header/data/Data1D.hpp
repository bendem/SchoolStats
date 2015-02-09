#ifndef DATA1D_HPP
#define DATA1D_HPP

#include "data/Data.hpp"
#include "utils/Comparable.hpp"

struct Data1DPointerComparator;

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

    friend struct Data1DPointerComparator;

};

struct Data1DPointerComparator {
    int operator()(Data* d1, Data* d2) {
        return static_cast<Data1D*>(d1)->compareTo(*static_cast<Data1D*>(d2));
    }
};

#endif
