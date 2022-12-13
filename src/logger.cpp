#include <iostream>
#include <string>
#include <cstdarg>
#include "include/logger.h"

using namespace std;

namespace logger {
	string RED_START = "\x1B[31m";
	string GREEN_START = "\x1B[32m";
	string END = "\033[0m";
	string get_string(const char* fmt, va_list args) {
		string result = "";
		while (*fmt != '\0') {
			if (*fmt == '%') {
				fmt ++;
				if (*fmt == '\0') break;
				switch (*fmt) {
					case 's':
						result += (string)(va_arg(args, const char*));
						break;
					case 'd':
						result += to_string(va_arg(args, int));
						break;
				}
			}
			else {
				result += *fmt;
			}
			fmt ++;
		}
		return result;
	}
	void error(const char* fmt...) {
		va_list args;
		va_start(args, fmt);
		string str = get_string(fmt, args);
		va_end(args);
		string result = RED_START + (string) str + END;
		cout << result << '\n';
	}
	void info(const char* fmt...) {
		va_list args;
		va_start(args, fmt);
		string str = get_string(fmt, args);
		va_end(args);
		string result = GREEN_START + (string) str + END;
		cout << result << '\n';
	}
}