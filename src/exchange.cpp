#include <iostream>
#include <cstring>
#include <sstream>
#include <regex>
#include <fstream>
#include <streambuf>
#include "include/exchange.h"
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
		route_ = head[1];
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
	Response::Response() {}
	void Response::add_main(string http_version, string status_code) {
		http_version_ = http_version; status_code_ = status_code;
	}
	void Response::add_body(string body) {
		body_ = body;
	}
	void Response::add_header(string key, string value) {
		headers_.push_back(new Header(key, value));
	}
	string Response::generate_str() {
		string response = "";
		response += http_version_ + " " + status_code_ + "\r\n";
		for (int i = 0; i < headers_.size(); i ++) {
			response += headers_[i] -> key_ + ": " + headers_[i] -> value_ + "\r\n";
		}
		response += "\r\n";
		response += body_;
		response += "\r\n\r\n";
		return response;
	}
	string render_file(string path) {
		ifstream file(path);
		if (!file.is_open()) {
			error("could not open the file %s", path.c_str());
			return "";
		}
		string str((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		return str;
	}
}