#pragma once
#include <vector>
#include <map>
#include <cstdio>
#include <array>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

struct host_info {
	std::string name;
	std::string IPv4;
	std::string MAC;
};
