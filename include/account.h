#pragma once

#include <string>

class account_section {
   public:
    static std::string extract_account_id(const std::string& line);
    static std::string extract_period(const std::string& line);

    static account_section* get() {
        return account ? account : account = new account_section;
    }

   private:
    static account_section* account;
};