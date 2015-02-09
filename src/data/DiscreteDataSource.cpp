#include "data/DiscreteDataSource.hpp"

DiscreteDataSource::DiscreteDataSource(string name, string subject,
    unsigned total, const List<Data*>& data)
        : DataSource(name, subject, total, DISCRETE, data) {}
