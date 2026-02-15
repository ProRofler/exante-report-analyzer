#include "account.h"

#include <chrono>

account_section* account_section::account = nullptr;

std::string account_section::extract_account_id(const std::string& line) {

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

std::string account_section::extract_period(const std::string& line) {
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
