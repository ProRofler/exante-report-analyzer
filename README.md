# EXANTE Report Analyzer

A C++ application for parsing and analyzing EXANTE broker reports and generating concise summaries of trading activity, including best and worst trades, frequency statistics, and performance insights.

## Usage

### Windows

#### Provide CSV file as an argument
```bat
EXANTE_Report_Analyzer.exe your_report.csv
```
### Windows

#### Provide CSV file as an argument
```bash
./EXANTE_Report_Analyzer your_report.csv
```

#### Or just use default file name
If a file named "report.csv" is in the same directory then it'll be read automatically

## Known Issues

- **UTF-8 encoding required**  
  The program currently only supports CSV files encoded in UTF-8. Files using other encodings (e.g., Windows-1251, ISO-8859-1) may fail to parse or produce incorrect results.

### Workarounds

#### Windows (PowerShell)
Convert a file to UTF-8:
```powershell
Get-Content input.csv | Set-Content -Encoding utf8 output.csv
```

Linux

Using iconv:
```bash
iconv -f WINDOWS-1251 -t UTF-8 input.csv -o output.csv
```
Replace WINDOWS-1251 with the actual source encoding if different.

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
- [x] Avoid unnecessary copies
- [ ] Profiling and optimization pass

---

## Build
- [x] CMake build system
- [x] Cross-platform (Linux / Windows)
- [x] Compiler warnings treated as errors
- [x] CI/CD workflow

---

## Future Ideas
- [ ] Visualization export (CSV for plotting)
- [ ] Support for additional brokers
