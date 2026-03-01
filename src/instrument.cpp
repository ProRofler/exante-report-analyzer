#include "instrument.h"

account_data::account_data(const std::string& account) : account_id(account) {}

void account_data::add_ticker(const std::string& ticker,
                              const instrument_data& data) {
    auto [it, inserted] = instruments.try_emplace(ticker, data);

    if (inserted) {
        it->second = data;
    } else {
        ++it->second.trades;
        it->second.pl += data.pl;
        it->second.diff += data.diff;
    }
}
