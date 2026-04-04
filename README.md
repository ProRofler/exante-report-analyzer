# EXANTE Report Analyzer

A C++ application for parsing and analyzing EXANTE broker reports and generating concise summaries of trading activity, including best and worst trades, frequency statistics, and performance insights.

---

## Goals
- [x] Parse EXANTE-generated reports
- [x] Normalize transaction data into internal structures
- [ ] Analyze trading performance
- [x] Generate human-readable summaries
- [x] Keep the system fast, deterministic, and dependency-light

---

## Core Features
- [x] Report parser (CSV)
- [x] Trade aggregation by instrument
- [x] Trades sorted from best to worst
- [x] Trade count statistics
- [ ] Win / loss ratio
- [ ] Average trade PnL

---

## Analysis & Metrics
- [x] Per-instrument PnL
- [x] Cumulative PnL

---

## Output
- [x] Console summary report
- [x] Sorted tables (best → worst trades)
- [ ] Configurable output verbosity
- [ ] Export summary to file (txt / json)

---

## Architecture
- [ ] Separate parsing from analytics
- [ ] No hidden state / deterministic processing
- [x] No heap allocations in hot paths (where possible)
- [x] STL-first, minimal third-party dependencies
- [ ] Easily extensible metrics system

---

## CLI
- [x] Input report path
- [ ] Output format selection
- [ ] Enable / disable specific metrics
- [ ] Wide encoding support

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
- [x] CMake build system
- [x] Cross-platform (Linux / Windows)
- [x] Compiler warnings treated as errors

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
