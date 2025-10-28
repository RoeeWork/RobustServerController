#pragma once

#include <vector>
#include <map>
#include <cstdio>
#include <array>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>

#include <nlohmann/json.hpp>

#define RESET  "\033[0m"
#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define BLUE   "\033[34m"
#define BOLD   "\033[1m"
#define UNDER  "\033[4m"

inline std::filesystem::path root = std::filesystem::canonical("/proc/self/exe").parent_path().parent_path();

struct host_info {
	std::string name;
	std::string IPv4;
	std::string MAC;
};

struct host_output {
	std::string name;
	std::string IPv4;
	std::string MAC;
	std::string status; // offline-online
};

void verbose_print(const std::string& msg, bool verbose);
