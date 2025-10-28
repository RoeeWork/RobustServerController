#include "Commands.h"

ControlWorker::ControlWorker() {}

void ControlWorker::Start() {
	verbose_print("[ControlWorker::Start()] starting ControlWorker::Start()...\n", verbose);
	verbose_print("[ControlWorker::Start()] starting arp-scan\n", verbose);
	std::vector<std::string> arpOut = arpScanOutput();
	verbose_print("[ControlWorker::Start()] done!\n", verbose);

	for (auto &h : this->chosenHosts) {
		host_output currHost;
		currHost.name = h.name;
		currHost.MAC = h.MAC;
		bool status = checkStatus(currHost.MAC, arpOut, currHost.IPv4);
		status ? currHost.status = "online" : currHost.status = "offline";
		this->hostOutputs.push_back(currHost);
	}
	PrintOutput(); 
	verbose_print("[ControlWorker::Start()] finished!\n", verbose);
}

void ControlWorker::PrintOutput() {
	verbose_print("[ControlWorker::PrintOutput()] printing output...\n", verbose);
	for (auto &h : this->hostOutputs) {
		std::cout << "==============" << h.name << "==============\n";
		std::cout << "status:\t" << h.status << '\n'
					<< "MAC:\t" << h.MAC << '\n'
					<< "IPv4:\t" << h.IPv4<< '\n';
	}
	std::cout << "=======================================\n";
	verbose_print("[ControlWorker::PrintOutput()] done!\n", verbose);
}
