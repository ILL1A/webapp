#ifndef _FORMAT_H_
#define _FORMAT_H_ 1
#include <iostream>

using namespace std;

namespace http_request {
	struct Headers {
		string key;
		string value;
	};
	class Request {
	public:
		Request();
		Request(int request_length, string request);
		const int get_request_length() const {
			return request_length_;
		}
		const string get_unformatted_request() const {
			return unformatted_request_;
		}
		const Headers* get_request_headers() const {
			return headers_;
		}
		const string get_request_body() const {
			return body_;
		}
	private:
		int request_length_;
		string unformatted_request_;
		Headers* headers_;
		string body_;
	};
}

#endif // _FORMAT_H_