#include <iostream>
#include <cstring>
#include <sstream>
#include <regex>
#include "include/format.h"
#include "include/logger.h"

using namespace std;
using namespace logger;

namespace http_request {
	Header::Header(string key, string value) : key_(key), value_(value) {}
	Request::Request() {}
	Request::Request(int request_length, string request) : request_length_(request_length), unformatted_request_(request) {}
	vector <string> tokenize(string str, string delim) {
		regex regex("\\" + delim);
		vector<string> out(
                    sregex_token_iterator(str.begin(), str.end(), regex, -1),
                    sregex_token_iterator()
                    );
		return out;
	}
	bool Request::format() {
		vector <string> splitted = tokenize(unformatted_request_, "\r\n\r\n{1}");
		if (splitted.empty()) {
			error("wrong http request format");
			return 0;
		}
		vector <string> headers = tokenize(splitted[0], "\r\n");
		if (headers.empty()) {
			error("wrong http request format (no headers)");
			return 0;
		}
		vector <Header*> formatted_headers;
		vector <string> head;
		head = tokenize(headers[0], " ");
		if (head.size() != 3) {
			error("wrong http request format (wrong first line structure)");
			return 0;
		}
		method_ = head[0];
		path_ = head[1];
		http_version_ = head[2];
		for (int i = 1; i < headers.size(); i ++) {
			vector <string> cur = tokenize(headers[i], ": ");
			formatted_headers.push_back(new Header(cur[0], cur[1]));
		}
		headers_ = formatted_headers;
		if (splitted.size() > 1) body_ = splitted[1];
		else body_ = "";
		return 1;
	}
}