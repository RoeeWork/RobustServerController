#include "Commands.h"

ControlWorker::ControlWorker() {}

void ControlWorker::Start() {
	verbose_print("[ControlWorker::Start()] starting ControlWorker::Start()...", verbose);
	verbose_print("[ControlWorker::Start()] starting arp-scan", verbose);
	std::vector<std::string> arpOut;
	try {
		arpOut = arpScanOutput();
	}
	catch (std::exception &e) {
		std::cerr << "[ControlWorker::Start()] ERROR running arp-scan: " << e.what() << "\n";
		return;
	}
	verbose_print("[ControlWorker::Start()] done!", verbose);

	for (auto &h : this->chosenHosts) {
		host_output currHost;
		currHost.name = h.name;
		currHost.MAC = h.MAC;
		try {
			bool status = checkStatus(currHost.MAC, arpOut, currHost.IPv4);
			status ? currHost.status = "online" : currHost.status = "offline";
		}
		catch (std::exception &e){
		    currHost.status = "error";
		    currHost.IPv4 = "N/A";
    		std::cerr << "[ControlWorker::Start()] ERROR checking host " << currHost.MAC
            		  << ": " << e.what() << "\n";
		}
		this->hostOutputs.push_back(currHost);
	}
	PrintOutput(); 
	verbose_print("[ControlWorker::Start()] finished!", verbose);
}

void ControlWorker::PrintOutput() {
	verbose_print("[ControlWorker::PrintOutput()] starting ControlWorker::PrintOutput()...", verbose);
	verbose_print("[ControlWorker::PrintOutput()] printing output...", verbose);
	std::cout << "\n";
	std::cout << BOLD 
			  << std::left
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
				  << color << std::setw(10) << h.status << RESET
				  << std::setw(20) << h.name
				  << std::setw(15) << h.IPv4
				  << std::setw(20) << h.MAC << RESET
				  << '\n';
	}
	std::cout << "\n";
	verbose_print("[ControlWorker::PrintOutput()] done!", verbose);
}
