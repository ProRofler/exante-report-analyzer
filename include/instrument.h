#pragma once

#include <string>
#include <unordered_map>

struct instrument_data {
    size_t trades = 0;
    float pl = 0.f;
    int diff = 0;
};

class account_data {
   public:
    account_data() = delete;
    account_data(const std::string& account);

    void add_ticker(const std::string& ticker, const instrument_data& data);

    bool operator==(const account_data& other) const noexcept {
        return account_id == other.account_id;
    }

   private:
    std::string account_id;
    std::unordered_map<std::string /*ticker*/, instrument_data> instruments;
};