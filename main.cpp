/* main.cpp */
#include "Commands.h"
#include "json_utils.h"

int main(int argc, char *argv[]) {
	if (argc == 2 && strcmp(argv[1],"--add-servers")) {
		AddServers add;
		add.Start();
	}
	if (argc == 1) {
		std::cout << "starting argc=1" << std::endl;
		ControlWorker cmd;
		std::cout << "created cmd object" << std::endl;
		cmd.Start();
		std::cout << "finished cmd object" << std::endl;
	}
	return 0;
}


