#ifndef _EXCHANGE_H_
#define _EXCHANGE_H_ 1
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
		const string get_request_route() const {
			return route_;
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
		string route_;
		string http_version_;
		vector<Header*> headers_;
		string body_;
	};
	class Response {
	public:
		Response();
		void add_main(string http_version, string status_code);
		void add_body(string body);
		void add_header(string key, string value);
		string generate_str();
		const string get_response_body() const {
			return body_;
		}
	private:
		string http_version_;
		string status_code_;
		vector<Header*> headers_;
		string body_;
	};
	string render_file(string path);
}

#endif // _EXCHANGE_H_