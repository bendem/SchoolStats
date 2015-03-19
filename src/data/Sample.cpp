#include "data/Sample.hpp"

Sample::Sample(string filename, unsigned column) {
    ifstream is(filename.c_str(), ios::in);
    Sanity::streamness(is, "Couldn't open " + filename);

    List<string> lines = StreamUtils::readLines(is);
    ConstIterator<string> it(lines);

    Log::log("Sample", "Getting context information");
    string name = (it++).get();
    string subject = StringUtils::split((it++).get(), ':')[column-1];
    string t = StringUtils::split((it++).get(), ':')[column-1];
    DataSourceType type = t == "C" ? CONTINOUS : DISCRETE;

    float firstInterval = -1, intervalSizes = -1;
    if(type == CONTINOUS) {
        Log::log("Sample", "Reading data intervals from user");
        cout << " Start of the first interval: ";
        firstInterval = StreamUtils::readFloat();

        cout << " Size of the intervals: ";
        while(true) {
            intervalSizes = StreamUtils::readFloat();
            if(intervalSizes <= 0) {
                cout << " Provide something greater than 0: ";
            } else {
                break;
            }
        }
    }

    // Read all the data from the file in a sorted list
    Log::log("Sample", "Reading file data");
    SortedList<float> dataRead;
    while(!it.end()) {
        List<string> columns = StringUtils::split(it.get(), ':');
        float value = StringUtils::stringToFloat(columns[column -1]);
        dataRead.add(value);
        ++it;
    }

    // Count the data and move them to a List<Data*>
    Log::log("Sample", "Moving data read to a List<Data*>");
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

    Log::log("Sample", "Building data source");
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

    Log::log("Sample", "Getting context information");
    string name = (it++).get();
    List<string> subjects = StringUtils::split((it++).get(), ':');
    List<string> types = StringUtils::split((it++).get(), ':');

    Log::log("Sample", "Reading file data");
    List<Data*> data;
    while(!it.end()) {
        List<string> values = StringUtils::split(it.get(), ':');
        data.add(new Data2D(
            StringUtils::stringToFloat(values[column1]),
            StringUtils::stringToFloat(values[column2])
        ));
        ++it;
    }

    Log::log("Sample", "Creating data source");
    this->dataSource = new DataSource2D(
        name,
        subjects[column1],
        subjects[column2],
        types[column1] == "C" ? CONTINOUS : DISCRETE,
        types[column2] == "C" ? CONTINOUS : DISCRETE,
        data
    );
}

Sample::~Sample() {
    delete this->dataSource;
}
