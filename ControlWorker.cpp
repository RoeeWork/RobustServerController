#include "Commands.h"

ControlWorker::ControlWorker() {}

void ControlWorker::Start() {
	std::cout << "[ControlWorker::Start()] started!\n";
	std::cout << "[ControlWorker::Start()] starting arp-scan\n";
	std::vector<std::string> arpOut = arpScanOutput();
	std::cout << "[ControlWorker::Start()] done!\n";

	for (auto &h : this->chosenHosts) {
		host_output currHost;
		currHost.name = h.name;
		currHost.MAC = h.MAC;
		bool status = checkStatus(currHost.MAC, arpOut, currHost.IPv4);
		status ? currHost.status = "online" : currHost.status = "offline";
		this->hostOutputs.push_back(currHost);
	}
	PrintOutput();
}

void ControlWorker::PrintOutput() {
	for (auto &h : this->hostOutputs) {
		std::cout << "==============" << h.name << "==============\n";
		std::cout << "status:\t" << h.status << '\n'
					<< "MAC:\t" << h.MAC << '\n'
					<< "IPv4:\t" << h.IPv4<< '\n';
	}
	std::cout << "=======================================\n";
}
