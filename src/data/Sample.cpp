#include <data/DiscreteDataSource.hpp>
#include "data/Sample.hpp"

Sample::Sample(string filename, unsigned column) {
    ifstream is(filename.c_str(), ios::in);
    Sanity::streamness(is, "Couldn't open " + filename);

    List<string> lines = StreamUtils::readLines(is);
    ConstIterator<string> it(lines);

    string name = (it++).get();
    List<string> titles = StringUtils::split((it++).get(), ':');
    List<string> types = StringUtils::split((it++).get(), ':');

    DataSourceType type = types[column - 1] == "C" ? CONTINOUS : DISCRETE;
    // TODO Use type somewhere somehow
    float firstInterval, intervalSizes; // int?
    if(type == CONTINOUS) {
        string tmp;
        cout << " Start of the first interval: ";
        getline(cin, tmp, cin.widen('\n'));
        firstInterval = StringUtils::stringToFloat(tmp); // TODO Handle invalid input

        cout << " Size of the intervals: ";
        getline(cin, tmp, cin.widen('\n'));
        intervalSizes = StringUtils::stringToFloat(tmp); // TODO Handle invalid input
    }

    SortedList<Data*> data(Data1DPointerComparator());
    while(!it.end()) {
        List<string> columns = StringUtils::split(it.get(), ':');
        float c1 = StringUtils::stringToFloat(columns[column -1]);

        // Only reading one column
        Optional<Data*> d = data.getFirstMatching(type == CONTINOUS ? /* Look for interval */ : /* Look for value */);
        // TODO If contains, add to existing Data1D instead of the list
        if(d.hasValue()) {
            static_cast<Data1D&>(d.get()).add(1);
        } else {
            data.add(new Data1D(1, c1));
        }
    }

    // TODO Params with that
    if(type == DISCRETE) {
        this->dataSource = new DiscreteDataSource();
    } else {
        // Copy to another list and add empty intervals
        List<Data*> dataWithEmptyIntervals;
        this->dataSource = new ContinousDataSource();
    }
}

Sample::Sample(string filename, unsigned column1, unsigned column2) {
    // TODO
}

Sample::Sample(const Sample& p) {
    // TODO Check if that's right
    ContinousDataSource* d = dynamic_cast<ContinousDataSource*>(p.dataSource);
    if(d) {
        this->dataSource = new ContinousDataSource(*d);
    } else {
        this->dataSource = new DataSource2D(*static_cast<DataSource2D*>(p.dataSource));
    }
}

Sample::~Sample() {
    delete this->dataSource;
}

void Sample::display() const {
}

Sample& Sample::operator=(Sample sample) {
    swap(this->dataSource, sample.dataSource);
    return *this;
}
