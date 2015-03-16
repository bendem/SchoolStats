#include "data/ContinousDataSource.hpp"

ContinousDataSource::ContinousDataSource(string name, string subject,
    unsigned totalCount, List<Data*>& data, float firstInterval, float intervalSizes)
        : DataSource(name, subject, totalCount, CONTINOUS, data) {
    this->firstInterval = firstInterval;
    this->intervalSizes = intervalSizes;
}
