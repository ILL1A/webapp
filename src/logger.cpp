#include <iostream>
#include <string>
#include "include/logger.h"

using namespace std;

namespace logger {
	const char* RED_START = "\x1B[31m";
	const char* GREEN_START = "\x1B[32m";
	const char* END = "\033[0m";
	void error(string msg) {
		printf("%serror: %s%s\n", RED_START, msg.c_str(), END);
	}
	void info(string msg) {
		printf("%sinfo: %s%s\n", GREEN_START, msg.c_str(), END);
	}
}