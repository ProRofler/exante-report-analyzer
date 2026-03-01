#include <iostream>
#include <fstream>

#include "account.h"
#include "lazyprofiler.h"

int main(int argc, char* argv[]) {
    std::string filename{"report.csv"};
    if (argc > 1) filename = argv[1];
    std::ifstream report(filename);

    if (report.is_open()) {
        std::cout << "************************************** \n"
                  << "Parsing file: " << filename << '\n'
                  << "************************************** \n\n";
    } else {
        std::cout << "Couldn't open the report file :(" << std::endl;
        return 1;
    }

    std::string line;

    std::string report_out;

    account inst("test");

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
