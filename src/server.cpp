#include <iostream> 
#include <string>
#include "include/logger.h"

using namespace std;
using namespace logger;

int get_port(string str) {
	if (str.size() > 6) return -1;
	int port = 0;
	for (int i = 0; i < str.size(); i ++) {
		if (str[i] < '0' || str[i] > '9') return -1;
		port = port * 10 + (str[i] - '0');
	}
	return port;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		error("you need to provide port");
		return 0;
	}
	int port = get_port((string)argv[1]);
	if (port == -1) {
		error("incorrect port");
		return 0;
	}
	info("listening on port: " + to_string(port));
}