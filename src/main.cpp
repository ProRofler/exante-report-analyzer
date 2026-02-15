#include <iostream>
#include <fstream>
#include <chrono>
#include <locale>
#include <codecvt>

#include "account.h"

enum class report_section { none, account };

int main() {
    std::ifstream report("report.csv");

    if (!report.is_open()) {
        std::cout << "Couldn't open the report file :(" << std::endl;
    } else {
        std::cout << "Got the report file :)\n\n"
                     "************************************** \n\n";
    }

    report_section current_section = report_section::none;

    // Account section

    std::string line;

    std::string report_out;

    auto start = std::chrono::steady_clock::now();

    while (std::getline(report, line)) {
        if (line.find("\"Costs and Charges Report:\"") == 0) {
            std::string period;
            account_section::get()->extract_period(period);
            if (!period.empty()) {
                report_out.append("Report period: " + period + "\n");
            }
            continue;
        }

        if (line.find("\"Account\"") == 0) {
            current_section = report_section::account;

            std::string account_id =
                account_section::get()->extract_account_id(line);

            report_out.append("Account:" + account_id + "\n");

            continue;
        }

        current_section = report_section::none;
    }
    auto stop = std::chrono::steady_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << report_out                             //
              << '\n'                                   //
              << "Time reading the file: " << duration  //
              << std::endl;

    return 0;
}
