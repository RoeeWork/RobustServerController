/* main.cpp */
#include "Commands.h"
#include "json_utils.h"

int main() {
	AddServers add;
	add.Start();
	std::cout << "chose hosts.\n";
	for (auto &p: add.chosenHosts) {
		std::cout << p.name << ":";
		std::cout << p.IPv4 << "\n";
	}
}


