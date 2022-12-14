#include <iostream>
#include <regex>
#include "include/validator.h"

using namespace std;

namespace validator {
	bool port_validate(const char* str) {
		regex port("^((6553[0-5])|(655[0-2][0-9])|(65[0-4][0-9]{2})|(6[0-4][0-9]{3})|([1-5][0-9]{4})|([0-5]{0,5})|([0-9]{1,4}))$");
		if (regex_match(str, port)) {
			return true;
		} else {
			return false;
		}
	}
}