#include <iostream> 
#include <string>
#include <regex> 
#include "include/logger.h"

using namespace std;
using namespace logger;

int get_port(const char* str) {
	regex port("^((6553[0-5])|(655[0-2][0-9])|(65[0-4][0-9]{2})|(6[0-4][0-9]{3})|([1-5][0-9]{4})|([0-5]{0,5})|([0-9]{1,4}))$");
	if (regex_match(str, port)) {
		return atoi(str);
	} else {
		return -1;
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		error("you need to provide port");
		return 0;
	}
	int port = get_port(argv[1]);
	if (port == -1) {
		error("incorrect port");
		return 0;
	}
	info("listening on port: %d", port);
}