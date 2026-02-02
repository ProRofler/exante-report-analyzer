# EXANTE Report Analyzer

A C++ application for parsing and analyzing EXANTE broker reports and generating concise summaries of trading activity, including best and worst trades, frequency statistics, and performance insights.

---

## Goals
- [ ] Parse EXANTE-generated reports
- [ ] Normalize transaction data into internal structures
- [ ] Analyze trading performance
- [ ] Generate human-readable summaries
- [ ] Keep the system fast, deterministic, and dependency-light

---

## Core Features
- [ ] Report parser (CSV)
- [ ] Trade aggregation by instrument
- [ ] Trades sorted from best to worst
- [ ] Most frequent instruments
- [ ] Trade count statistics
- [ ] Win / loss ratio
- [ ] Average trade PnL

---

## Analysis & Metrics
- [ ] Per-instrument PnL
- [ ] Cumulative PnL

---

## Output
- [ ] Console summary report
- [ ] Sorted tables (best → worst trades)
- [ ] Configurable output verbosity
- [ ] Export summary to file (txt / json)

---

## Architecture
- [ ] Separate parsing from analytics
- [ ] No hidden state / deterministic processing
- [ ] No heap allocations in hot paths (where possible)
- [ ] STL-first, minimal third-party dependencies
- [ ] Easily extensible metrics system

---

## CLI
- [ ] Input report path
- [ ] Output format selection
- [ ] Enable / disable specific metrics

---

## Testing
- [ ] Unit tests for parsers
- [ ] Unit tests for analytics
- [ ] Edge case handling (empty reports, malformed rows)

---

## Performance
- [ ] Handle large reports efficiently
- [ ] Avoid unnecessary copies
- [ ] Profiling and optimization pass

---

## Build
- [ ] CMake build system
- [ ] Cross-platform (Linux / Windows)
- [ ] Compiler warnings treated as errors

---

## Documentation
- [ ] Usage examples
- [ ] Architecture overview

---

## Future Ideas
- [ ] Visualization export (CSV for plotting)
- [ ] Support for additional brokers

---

## Status
🚧 Work in progress
