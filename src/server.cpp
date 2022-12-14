#include <iostream> 
#include <string>
#include "include/logger.h"
#include "include/validator.h"

using namespace std;
using namespace logger;
using namespace validator;

int get_port(const char* str) {
	if (port_validate(str)) return atoi(str);
	else return -1;
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