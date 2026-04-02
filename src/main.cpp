#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "account.h"
#include "lazyprofiler.h"

static std::string strip_quotes(const std::string& s) {
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
        return s.substr(1, s.size() - 2);
    return s;
}

static std::vector<std::string> split_tsv(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;
    while (std::getline(ss, field, '\t')) fields.push_back(strip_quotes(field));
    return fields;
}

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

    account inst("test");

    // Skip all lines until the header row
    START_PROFILE(reading_duration);
    while (std::getline(report, line)) {
        if (line.find("Transaction ID") != std::string::npos) break;
    }

    while (std::getline(report, line)) {
        if (line.empty()) continue;

        auto fields = split_tsv(line);
        if (fields.size() < 9) continue;

        const std::string& op_type = fields[4];  // Operation Type
        const std::string& symbol = fields[2];   // Symbol ID

        if (symbol == "None") continue;

        if (op_type == "TRADE") {
            const std::string& asset = fields[7];  // Asset
            if (asset == symbol) {
                // Security leg: Sum is the share count (signed), don't count as a separate trade
                const int diff = static_cast<int>(std::stof(fields[6]));
                inst.add_instrument(symbol, 0.f, diff, false);
            } else {
                // Cash leg: EUR equivalent is the money flow (negative=paid, positive=received)
                const float pl = std::stof(fields[8]);
                inst.add_instrument(symbol, pl, 0);
            }
        } else if (op_type == "COMMISSION") {
            const float commission = std::stof(fields[8]);  // EUR equivalent
            inst.add_commission(symbol, commission);
        }
    }
    END_PROFILE(reading_duration);

    inst.print();
    std::cout << "Time reading the file: " << reading_duration << std::endl;

    return 0;
}
