#include <iostream>
#include <fstream>

#include "instrument.h"
#include "lazyprofiler.h"

int main() {
    std::ifstream report("report.csv");

    if (!report.is_open()) {
        std::cout << "Couldn't open the report file :(" << std::endl;
    } else {
        std::cout << "Got the report file :)\n\n"
                     "************************************** \n\n";
    }

    std::string line;

    std::string report_out;

    instrument inst("test", "test");

    START_PROFILE(reading_duration);
    while (std::getline(report, line)) {
        //
    }
    END_PROFILE(reading_duration);

    std::cout << report_out                                     //
              << '\n'                                           //
              << "Time reading the file: " << reading_duration  //
              << std::endl;

    return 0;
}
