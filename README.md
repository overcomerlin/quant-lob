# Study note: quant-lob

![C++](https://img.shields.io/badge/Language-C++17-red.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

## 📖 Overview

A study note for low-latency order matching engine implemented in C++, designed to demonstrate core concepts of high-frequency trading (HFT) systems, including memory optimization, efficient data structures, and FIFO matching logic.

## 🚀 Key Features

* **Low Latency Architecture:** Utilizes a custom **Object Pool** to prevent runtime heap allocation overhead (`new`/`delete`), minimizing latency spikes during high-load periods.
* **Price-Time Priority:** Implements standard **FIFO** matching logic using Price Levels.
* **Efficient Data Structures:** Uses `std::map` for ordered price levels and Linked Lists for constant-time O(1) order insertion/deletion within levels.
* **Performance:** Capable of processing **50,000+ orders per second** (single-threaded benchmark) on standard hardware.

## 🛠 Tech Stack

* **Language:** C++ 17
* **Build System:** CMake
* **Containerization:** Docker (Multi-stage build)
* **Testing:** Google Test (Unit Tests)

## 🏗 System Architecture

1.  **Object Pool:** Pre-allocates memory for Order objects to ensure cache locality and zero allocation during trading hours.
2.  **Matching Engine:** Handles incoming Buy/Sell requests.
    * If a match exists (Spread crossed): Executes trade immediately.
    * If no match: Places order into the Order Book (Maker).

## ⚡ Quick Start

### 1. Build using Docker (Recommended)
This guarantees the environment matches the development setup.

```bash
docker build -t quant-lob .
docker run quant-lob
```

### 2. Build using CMake (Optional)

```bash
mkdir build && cd build
cmake .. && make
./QuantLOB
```

## 👨‍💻 Author

**Jacob Lin**
_Algorithm Engineer & Full-Stack Developer_
[LinkedIn](https://www.linkedin.com/in/dachunglin) | [Email](mailto:overcomerlin@gmail.com)

_"A ranger soaring through the world of algorithms."_