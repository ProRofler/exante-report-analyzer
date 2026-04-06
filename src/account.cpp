#include "account.h"

#include <iomanip>
#include <sstream>
#include "lazyprofiler.h"

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

void account::record_trade_day(const std::string& date) {
    // date is "YYYY-MM-DD HH:MM:SS", take only the date part
    if (traded_dates.emplace(date.substr(0, 10)).second) ++trading_days;
}

void account::print() const {
    START_PROFILE(vec_copy);
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
    END_PROFILE(vec_copy);

    std::cout << "Vector copy\\sort time: " << vec_copy << '\n';

    // Determine column widths dynamically
    unsigned col_ticker = 6;  // "Ticker"
    for (const auto& [ticker, _] : sorted)
        col_ticker =
            std::max(col_ticker, static_cast<unsigned>(ticker->size()) - 2);
    col_ticker += 2;

    constexpr unsigned col_trades = 8;
    constexpr unsigned col_pl = 10;
    constexpr unsigned col_comm = 12;

    const unsigned total_width =
        col_ticker + col_trades + col_pl + col_comm + 16;

    auto divider = [&](char c) {
        std::cout << std::string(total_width, c) << '\n';
    };

    divider('=');
    std::cout << "  Account: " << account_id << '\n';
    std::cout << "  Total trading days: " << trading_days << '\n';
    divider('=');

    std::cout << std::left << std::setw(static_cast<int>(col_ticker))
              << "Ticker" << std::right << std::setw(col_trades) << "Trades"
              << std::setw(col_pl) << "P/L EUR" << std::setw(col_comm)
              << " Commission EUR" << '\n';
    divider('-');

    std::cout << std::fixed << std::setprecision(2);
    float total_pl = 0.f, total_commission = 0.f;
    for (const auto& [ticker, data] : sorted) {
        if (data->diff != 0) break;  // skip open positions
        std::cout << std::left << std::setw(static_cast<int>(col_ticker))
                  << *ticker << std::right << std::setw(col_trades)
                  << data->trades << std::setw(col_pl) << data->pl
                  << std::setw(col_comm) << data->commission << '\n';
        total_pl += data->pl;
        total_commission += data->commission;
    }
    std::cout << std::left << std::setw(static_cast<int>(col_ticker)) << "TOTAL"
              << std::right << std::setw(col_trades) << "" << std::setw(col_pl)
              << total_pl << std::setw(col_comm) << total_commission << '\n';
    divider('=');
}