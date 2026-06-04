#!/bin/bash
set -euo pipefail


DEPS=(
    build-essential
    cmake
    libboost-program-options-dev
    nlohmann-json3-dev
    arp-scan
)

sudo apt update
sudo apt install -y "${DEPS[@]}"
echo -e "\033[32m[OK] Dependencies installed.\033[0m"

PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="${BUILD_DIR:-$PROJECT_DIR/build}"

cmake -S "$PROJECT_DIR" -B "$BUILD_DIR"
cmake --build "$BUILD_DIR" -j "$(nproc)"
echo -e "\033[32mBuild Successful.\033[0m"

# add to PATH temporarily
export PATH="$BUILD_DIR:$PATH"
echo -e "\033[32mAdded to PATH successfully\033[0m"