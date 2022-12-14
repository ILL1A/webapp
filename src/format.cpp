#include <iostream>
#include "include/format.h"

using namespace std;

namespace http_request {
	Request::Request() {}
	Request::Request(int request_length, string request) : request_length_(request_length), unformatted_request_(request) {}
}