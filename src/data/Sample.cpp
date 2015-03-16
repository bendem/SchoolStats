#include "data/Sample.hpp"

Sample::Sample(string filename, unsigned column) {
    ifstream is(filename.c_str(), ios::in);
    Sanity::streamness(is, "Couldn't open " + filename);

    List<string> lines = StreamUtils::readLines(is);
    ConstIterator<string> it(lines);

    cerr << "Getting context information" << endl;
    string name = (it++).get();
    string subject = StringUtils::split((it++).get(), ':')[column-1];
    string t = StringUtils::split((it++).get(), ':')[column-1];
    DataSourceType type = t == "C" ? CONTINOUS : DISCRETE;

    float firstInterval = 0, intervalSizes = 0;
    if(type == CONTINOUS) {
        cerr << "Reading data intervals from user" << endl;
        string tmp;
        cout << " Start of the first interval: ";
        getline(cin, tmp, cin.widen('\n'));
        firstInterval = StringUtils::stringToFloat(tmp); // TODO Handle invalid input

        cout << " Size of the intervals: ";
        getline(cin, tmp, cin.widen('\n'));
        intervalSizes = StringUtils::stringToFloat(tmp); // TODO Handle invalid input
    }

    // Read all the data from the file in a sorted list
    cerr << "Reading file data" << endl;
    SortedList<float> dataRead;
    while(!it.end()) {
        List<string> columns = StringUtils::split(it.get(), ':');
        float value = StringUtils::stringToFloat(columns[column -1]);
        dataRead.add(value);
        ++it;
    }

    // Count the data and move them to a List<Data*>
    cerr << "Moving data read to a List<Data*>" << endl;
    List<Data*> data;
    unsigned totalCount = 0;
    if(type == DISCRETE) {
        ConstIterator<float> it(dataRead);
        float prev = (it++).get();
        unsigned count = 1;
        while(!it.end()) {
            if(it.get() == prev) {
                ++count;
            } else {
                data.add(new Data1D(count, prev));
                totalCount += count;
                prev = it.get();
                count = 1;
            }
            ++it;
        }
    } else {
        ConstIterator<float> it(dataRead);
        Sanity::truthness(it.get() >= firstInterval, "WHY YOU GIVE STUPID VALUES?");
        float prev = firstInterval + intervalSizes / 2;
        unsigned count = 0;
        while(!it.end()) {
            while(!it.end() && it.get() < prev + intervalSizes / 2) {
                ++count;
                ++it;
            }
            data.add(new Data1D(count, prev));
            totalCount += count;
            count = 0;
            prev += intervalSizes;
        }
    }

    cerr << "Building data source" << endl;
    if(type == DISCRETE) {
        this->dataSource = new DiscreteDataSource(name, subject, totalCount, data);
    } else {
        this->dataSource = new ContinousDataSource(
            name, subject, totalCount,
            data, firstInterval, intervalSizes
        );
    }
}

Sample::Sample(string filename, unsigned column1, unsigned column2) {
    ifstream is(filename.c_str(), ios::in);
    Sanity::streamness(is, "Couldn't open " + filename);

    // These are the real indexes
    --column1;
    --column2;

    List<string> lines = StreamUtils::readLines(is);
    ConstIterator<string> it(lines);

    cerr << "Getting context information" << endl;
    string name = (it++).get();
    List<string> subjects = StringUtils::split((it++).get(), ':');
    List<string> types = StringUtils::split((it++).get(), ':');

    cerr << "Reading file data" << endl;
    List<Data*> data;
    while(!it.end()) {
        List<string> values = StringUtils::split(it.get(), ':');
        data.add(new Data2D(
            StringUtils::stringToFloat(values[column1]),
            StringUtils::stringToFloat(values[column2])
        ));
        ++it;
    }

    cerr << "Creating data source" << endl;
    this->dataSource = new DataSource2D(
        name,
        subjects[column1],
        subjects[column2],
        types[column1] == "C" ? CONTINOUS : DISCRETE,
        types[column2] == "C" ? CONTINOUS : DISCRETE,
        data
    );
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
    // TODO
    //this->dataSource->display();
}

Sample& Sample::operator=(Sample sample) {
    swap(this->dataSource, sample.dataSource);
    return *this;
}
