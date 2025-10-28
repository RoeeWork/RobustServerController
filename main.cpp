/* main.cpp */
#include "Commands.h"
#include "json_utils.h"


void verbose_print(const std::string& msg, bool verbose) {
    if (verbose) std::cout << msg << std::endl;
}

bool verbose = false;

int main(int argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--verbose" || arg == "-v") {
            verbose = true;
        } else if (arg == "--add-servers") {
			AddServers add;
			add.Start();
			return 0;

		} else {
			std::cout << "arguement invalid.";
			return 0;
		}
    }
	ControlWorker cmd;
	cmd.Start();
	return 0;
}


