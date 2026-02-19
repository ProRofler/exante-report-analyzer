#pragma once

#include <string>

class instrument {
   public:
    instrument() = delete;
    instrument(const std::string& account, const std::string& ticker);

   private:
    std::string _account;
    std::string _ticker;
    int trades = 0;
    float pl = 0.f;
    int diff = 0;
};