#include <iostream>
#include <fstream>
#include <chrono>

#include "instrument.h"

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

    auto start = std::chrono::steady_clock::now();
    while (std::getline(report, line)) {
                //
    }
    auto stop = std::chrono::steady_clock::now();

    auto reading_duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << report_out                                     //
              << '\n'                                           //
              << "Time reading the file: " << reading_duration  //
              << std::endl;

    return 0;
}
