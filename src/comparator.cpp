#include <iostream>
#include <regex>
#include <string>

#include "include/comparator.h"

using namespace std;

namespace comparator {
	bool port_validate(const char* str) {
		regex port("^((6553[0-5])|(655[0-2][0-9])|(65[0-4][0-9]{2})|(6[0-4][0-9]{3})|([1-5][0-9]{4})|([0-5]{0,5})|([0-9]{1,4}))$");
		return regex_match(str, port);
	}
	bool check_start(string start, string str) {
		string query = string("^") + "(" + start + ").*";
		regex substr(query);
		return regex_match(str.c_str(), substr);
	}
}