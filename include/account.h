#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct ticker_data {
    size_t trades = 0;
    float pl = 0.f;
    int diff = 0;
    float commission = 0.f;
};

class account {
   public:
    account() = delete;
    account(const account& other) = delete;
    account(const std::string& account);

    void add_ticker(const std::string& ticker, const ticker_data& data);
    void add_instrument(const std::string& ticker, float pl, int diff,
                        bool count_trade = true);
    void add_commission(const std::string& ticker, float commission);
    void record_trade_day(const std::string& date);
    void print() const;

    bool operator==(const account& other) const noexcept {
        return account_id == other.account_id;
    }

   private:
    std::string account_id;
    size_t trading_days = 0;
    std::unordered_set<std::string> traded_dates;
    std::unordered_map<std::string /*ticker*/, ticker_data> instruments;
};