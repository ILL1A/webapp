#ifndef _FORMAT_H_
#define _FORMAT_H_ 1
#include <iostream>
#include <vector>

using namespace std;

namespace http_request {
	struct Header {
		Header(string key, string value);
		string key_;
		string value_;
	};
	class Request {
	public:
		Request();
		Request(int request_length, string request);
		bool format();
		const int get_request_length() const {
			return request_length_;
		}
		const string get_unformatted_request() const {
			return unformatted_request_;
		}
		const string get_request_method() const {
			return method_;
		}
		const string get_request_path() const {
			return path_;
		}
		const string get_http_version() const {
			return http_version_;
		}
		const vector<Header*> get_request_headers() const {
			return headers_;
		}
		const string get_request_body() const {
			return body_;
		}
	private:
		int request_length_;
		string unformatted_request_;
		string method_;
		string path_;
		string http_version_;
		vector<Header*> headers_;
		string body_;
	};
}

#endif // _FORMAT_H_