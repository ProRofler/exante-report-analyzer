#pragma once

#include <string>
#include <unordered_map>

struct ticker_data {
    size_t trades = 0;
    float pl = 0.f;
    int diff = 0;
};

class account {
   public:
    account() = delete;
    account(const std::string& account);

    void add_ticker(const std::string& ticker, const ticker_data& data);

    bool operator==(const account& other) const noexcept {
        return account_id == other.account_id;
    }

   private:
    std::string account_id;
    std::unordered_map<std::string /*ticker*/, ticker_data> instruments;
};