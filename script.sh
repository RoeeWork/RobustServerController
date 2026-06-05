#!/bin/bash
set -euo pipefail

detect_pm() {
  if command -v apt &>/dev/null; then echo apt; return; fi
  if command -v dnf &>/dev/null; then echo dnf; return; fi
  if command -v pacman &>/dev/null; then echo pacman; return; fi
}

is_rhel_like() {
  [[ -f /etc/os-release ]] || return 1
  # shellcheck source=/dev/null
  source /etc/os-release
  case "${ID:-}" in
    rhel|centos|rocky|almalinux|ol|scientific) return 0 ;;
    *) return 1 ;;
  esac
}

ensure_epel() {
  is_rhel_like || return 0
  if rpm -q epel-release &>/dev/null; then return 0; fi
  echo "Installing EPEL (required for json-devel on RHEL)..."
  sudo dnf install -y epel-release
}

install_deps() {
  local pm="$1"; shift
  local pkgs=("$@")

  case "$pm" in 
    apt)
      sudo apt update
      sudo apt install -y "${pkgs[@]}"
      ;;
    dnf)
      sudo dnf install -y "${pkgs[@]}"
      ;;
    pacman)
      sudo pacman -Sy --needed --noconfirm "${pkgs[@]}"
      ;;
    *) echo "Unsupported package manager" >&2; exit 1
      ;;
  esac
}

PM="$(detect_pm || true)"
case "$PM" in
    apt)    DEPS=(build-essential cmake libboost-program-options-dev nlohmann-json3-dev arp-scan) ;;
    dnf)    DEPS=(gcc-c++ make cmake boost-devel json-devel arp-scan) ;;
    pacman) DEPS=(base-devel cmake boost nlohmann-json arp-scan) ;;
    *)      echo "No supported package manager found" >&2; exit 1 ;;
esac

[[ "$PM" == "dnf" ]] && ensure_epel
install_deps "${PM}" "${DEPS[@]}"
echo -e "\033[32m[OK] Dependencies installed.\033[0m"

PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="${BUILD_DIR:-$PROJECT_DIR/build}"

cmake -S "$PROJECT_DIR" -B "$BUILD_DIR"
cmake --build "$BUILD_DIR" -j "$(nproc)"
echo -e "\033[32mBuild Successful.\033[0m"

sudo install -m 755 "$BUILD_DIR/rsc" /usr/local/bin/
echo -e "\033[32mInstalled rsc to /usr/local/bin.\033[0m"
