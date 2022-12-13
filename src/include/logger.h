#include <iostream>
#include <string>

using namespace std;

namespace logger {
	void error(const char* fmt...);
	void info(const char* fmt...);
}