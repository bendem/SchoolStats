#include <iostream>

#include "data/Sample.hpp"
#include "statistics/StatisticalSerie1D.hpp"
#include "statistics/StatisticalSerie2D.hpp"
#include "utils/StringUtils.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Sample* E1;
    switch (argc) {
        case 2:
            cout << "Etude 1D" << endl;
            E1 = new Sample(argv[1], 1);
            E1->display();
            StatisticalSerie1D C1D(E1);
            C1D.displayReport();
            break;
        case 3:
            cout << "Etude 1D" << endl;
            E1 = new Sample(argv[1], StringUtils::stringToUnsigned(argv[2]));
            E1->display();
            StatisticalSerie1D C1D(E1);
            C1D.displayReport();
            break;
        case 4:
            cout << "Etude 2D" << endl;
            E1 = new Sample(argv[1], StringUtils::stringToUnsigned(argv[2]), StringUtils::stringToUnsigned(argv[3]));
            StatisticalSerie2D C2D(E1);
            C2D.display();
            C2D.forecast();
            break;
    }
    return 0;
}
