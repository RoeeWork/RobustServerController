#include "HandleCommand.hpp"


//TODO: change this shit wtf
void HandleCommand::printHosts(){
    std::vector<std::string> scanOutput;

    try{
        scanOutput = arpScanOutput();
    }catch (std::exception &e) {
		std::cerr << "[ControlWorker::Start()] ERROR running arp-scan: " << e.what() << "\n";
		return;
    }

    for (auto &h : this->chosenHosts) {
        setName(h.name);
        setIPv4Address(h.IPV4);
        setMACAddress(h.MAC);
        setStatus(h.status);
        
        try {
			bool status = checkStatus(h.MAC, scanOutput, h.IPv4);
            if (status){
                setStatus("online");
            }
            else{
			    setStatus("offline");
            }
		}
		catch (std::exception &e){
		    currHost.status = "error";
		    currHost.IPv4 = "N/A";
    		std::cerr << "[ControlWorker::Start()] ERROR checking host " << currHost.MAC << ": " << e.what() << "\n";
		}	
    }

	PrintOutput(); 
}

void HandleCommand::addMultipleHosts() {
	std::vector<Host> foundHosts = ArpUtils::scanHosts();
	std::vector<Host> newChosenHosts = HandleOutput::StartChooseHostsLoop(foundHosts);
	JsonUtils::saveHostsToFile(newChosenHosts, JsonUtils::JSON_FILE_PATH);
	HostList::populateChosenHosts();
 
	std::cout << "[HandleCommand::addMultipleHosts()] done!\n";
}
