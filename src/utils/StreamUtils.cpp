#include "utils/StreamUtils.hpp"

List<string> StreamUtils::readLines(istream& is) {
    List<string> lines;
    string line;
    while(is.peek() != EOF) {
        getline(is, line, is.widen('\n'));
        lines.add(line);
    }
    return lines;
}

string StreamUtils::read() {
    string tmp;
    getline(cin, tmp, cin.widen('\n'));
    return tmp;
}

float StreamUtils::readFloat() {
    while(true) {
        try {
            return StringUtils::stringToFloat(read());
        } catch(invalid_argument e) {
            cout << "Error: '" << e.what() << "', try again: " << endl;
        }
    }
}

unsigned StreamUtils::readUnsignedInt() {
    while(true) {
        try {
            return StringUtils::stringToUnsigned(read());
        } catch(invalid_argument e) {
            cout << "Error: '" << e.what() << "', try again: " << endl;
        }
    }
}
