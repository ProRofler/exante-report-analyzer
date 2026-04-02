#include "account.h"

#include <iomanip>
#include <sstream>

account::account(const std::string& account) : account_id(account) {}

void account::add_ticker(const std::string& ticker, const ticker_data& data) {
    auto [it, inserted] = instruments.try_emplace(ticker, data);

    if (inserted) {
        it->second = data;
    } else {
        ++it->second.trades;
        it->second.pl += data.pl;
        it->second.diff += data.diff;
    }
}

void account::add_instrument(const std::string& ticker, float pl, int diff,
                             bool count_trade) {
    auto [it, inserted] = instruments.try_emplace(
        ticker, ticker_data{count_trade ? 1u : 0u, pl, diff});

    if (!inserted) {
        if (count_trade) ++it->second.trades;
        it->second.pl += pl;
        it->second.diff += diff;
    }
}

void account::add_commission(const std::string& ticker, float commission) {
    auto [it, inserted] = instruments.try_emplace(ticker, ticker_data{});
    it->second.commission += commission;
}

void account::print() const {
    // Build sorted view: closed positions by pl desc, then open positions by pl
    // desc
    using pair_t = std::pair<const std::string*, const ticker_data*>;
    std::vector<pair_t> sorted;
    sorted.reserve(instruments.size());
    for (const auto& [ticker, data] : instruments)
        sorted.push_back({&ticker, &data});

    std::sort(sorted.begin(), sorted.end(),
              [](const pair_t& a, const pair_t& b) {
                  const bool a_open = a.second->diff != 0;
                  const bool b_open = b.second->diff != 0;
                  if (a_open != b_open) return b_open;  // closed before open
                  return a.second->pl > b.second->pl;   // higher pl first
              });

    // Determine column widths dynamically
    size_t col_ticker = 6;  // "Ticker"
    for (const auto& [ticker, _] : sorted)
        col_ticker = std::max(col_ticker, ticker->size());
    col_ticker += 2;

    constexpr int col_trades = 8;
    constexpr int col_pl = 10;
    constexpr int col_diff = 7;
    constexpr int col_comm = 12;

    const int total_width = static_cast<int>(col_ticker) + col_trades + col_pl +
                            col_diff + col_comm + 16;

    auto divider = [&](char c) {
        std::cout << std::string(total_width, c) << '\n';
    };

    divider('=');
    std::cout << "  Account: " << account_id << '\n';
    divider('=');

    std::cout << std::left << std::setw(static_cast<int>(col_ticker))
              << "Ticker" << std::right << std::setw(col_trades) << "Trades"
              << std::setw(col_pl) << "P/L" << std::setw(col_diff) << "Diff"
              << std::setw(col_comm) << "Commission" << '\n';
    divider('-');

    bool in_open_section = false;
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& [ticker, data] : sorted) {
        if (!in_open_section && data->diff != 0) {
            divider('-');
            std::cout << "  (open positions)\n";
            divider('-');
            in_open_section = true;
        }
        std::cout << std::left << std::setw(static_cast<int>(col_ticker))
                  << *ticker << std::right << std::setw(col_trades)
                  << data->trades << std::setw(col_pl) << data->pl
                  << std::setw(col_diff) << data->diff << std::setw(col_comm)
                  << data->commission << '\n';
    }
    divider('=');
}