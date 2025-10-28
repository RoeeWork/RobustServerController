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
	std::cout << "\n";
	std::cout << BOLD 
			  << std::left
			  << std::setw(10) << ""
			  << std::setw(10) << "STATUS"
			  << std::setw(20) << "NAME"
			  << std::setw(15) << "IPV4"
			  << std::setw(20) << "MAC"
			  << RESET
			  << '\n';

	for (auto &h : this->hostOutputs) {
        std::string color = (h.status == "online") ? GREEN : RED;
		std::cout << BLUE
				  << std::left 
				  << std::setw(10) << ""
				  << color << std::setw(10) << h.status << RESET
				  << std::setw(20) << h.name
				  << std::setw(15) << h.IPv4
				  << std::setw(20) << h.MAC << RESET
				  << '\n';
	}
	std::cout << "\n";
	verbose_print("[ControlWorker::PrintOutput()] done!\n", verbose);
}
