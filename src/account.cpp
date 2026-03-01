#include "account.h"

account::account(const std::string& account) : account_id(account) {}

void account::add_ticker(const std::string& ticker,
                              const ticker_data& data) {
    auto [it, inserted] = instruments.try_emplace(ticker, data);

    if (inserted) {
        it->second = data;
    } else {
        ++it->second.trades;
        it->second.pl += data.pl;
        it->second.diff += data.diff;
    }
}
