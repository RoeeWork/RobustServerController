#include "HandleCommand.hpp"
void HandleCommand::changeHostName(std::string oldName,std::string newName){
	HostList searchList;
	// if the names are equal there is no need for a change
	// NOTE: should we change this so the user will get a notice that nothing changed?
	if(oldName == newName){
		return;
	}

}
