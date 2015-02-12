#ifndef DATASOURCE1D_HPP
#define DATASOURCE1D_HPP

#include "data/DataSource.hpp"

class ContinousDataSource : public DataSource {

private:
    float firstInterval;
    float intervalSizes;

public:
    ContinousDataSource(string, string, unsigned, const List<Data*>&, float, float);

    float getFirstInterval() const;
    float getIntervalSizes() const;

};

inline float ContinousDataSource::getFirstInterval() const {
    return this->firstInterval;
}

inline float ContinousDataSource::getIntervalSizes() const {
    return this->intervalSizes;
}

#endif
