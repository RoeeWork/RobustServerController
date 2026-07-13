#include <vector>
#include <iostream>
#include "../host/Host.hpp"

class HandleOutput {
	public:
		// The contents of RSC's help command.
		// WARNING: DO NOT USE TABS, ONLY SPACES!
		static const std::string HELP_TEXT;

		// pretty prints hosts in chosenHosts as a table.
		// TODO: change name.
		static void printHostVectorTable(); 

		static std::vector<Host> StartChooseHostsLoop(std::vector<Host> foundHosts);

		// pretty prints hosts in chosenHosts as a numbered table.
		// only prints ipv4 and mac.
		static void printHostVectorNumberedTable(std::vector<Host> hosts); 

		// prints the numbered host table header.
		// TODO: seems unintuitive.
		static void printNumberedTableHeader(int  rowNumberColumnMargin, int IPv4ColumnMargin, int MACColumnMargin);

		// prints a new row to the numbered table.
		// TODO: seems unintuitive.
		static void printNumberedTableHostRow(int rowNumber, Host& h, int  rowNumberColumnMargin, int IPv4ColumnMargin, int MACColumnMargin);

		// prints msg if verbose is equal to true. 
		static void verbosePrint(const std::string& msg, bool verbose);
		
};
