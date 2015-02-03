#include <data/Data1D.hpp>
#include <data/Data2D.hpp>
#include "data/Sample.hpp"

Sample::Sample(string filename, unsigned column1, unsigned column2) {
    ifstream is(filename.c_str(), ios::in);
    Sanity::streamness(is, "Couldn't open " + filename);
    List<string> lines = StreamUtils::readLines(is);
    ConstIterator<string> it(lines);

    string name = (it++).get();
    List<string> titles = StringUtils::split((it++).get(), ':');
    List<string> types = StringUtils::split((it++).get(), ':');

    DataSourceType type = types[column1 - 1] == "C" ? CONTINOUS : DISCRETE;

    while(!it.end()) {
        cout << (it++).get() << endl;
    }
}

void Sample::display() const {
}
