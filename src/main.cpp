#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <locale>
#include <codecvt>


enum class report_section { none, account };

std::string extract_period(const std::string& line) {
    const std::string key = "Costs and Charges Report:";
    auto pos = line.find(key);
    if (pos == std::string::npos) return {};

    std::string period = line.substr(pos + key.size());

    // Trim spaces
    auto trim = [](std::string& s) {
        while (!s.empty() && std::isspace(s.front())) s.erase(s.begin());
        while (!s.empty() && std::isspace(s.back())) s.pop_back();
    };

    trim(period);

    // Remove surrounding quotes if present
    if (!period.empty() && period.front() == '"') period.erase(0, 1);
    if (!period.empty() && period.back() == '"') period.pop_back();

    return period;
}

std::string extract_account_id(const std::string& line) {
    std::stringstream ss(line);
    std::string key, value;

    std::getline(ss, key, '\t');
    std::getline(ss, value, '\t');

    auto stripQuotes = [](std::string s) {
        if (!s.empty() && s.front() == '"') s.erase(0, 1);
        if (!s.empty() && s.back() == '"') s.pop_back();
        return s;
    };

    key = stripQuotes(key);
    value = stripQuotes(value);

    if (key == "Account") return value;

    return {};
}

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
            extract_period(period);
            if (!period.empty()) {
                report_out.append("Report period: " + period + "\n");
            }
            continue;
        }

        if (line.find("\"Account\"") == 0) {
            current_section = report_section::account;

            std::string account_id = extract_account_id(line);

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
