#include <iostream> 
#include <string>
#include <thread>
#include "include/logger.h"
#include "include/validator.h"
#include "include/socket.h"
#include "include/format.h"

using namespace std;
using namespace logger;
using namespace validator;
using namespace http_request;

void connection_handler(Socket* client_socket) {
	string message = "successfully responded";
	Request* resp = new Request();
	while ((resp = client_socket -> socket_read()) -> get_request_length() > 0) {
		resp -> format();
		info("server: got message from %s:%d: %s", client_socket -> get_socket_host().c_str(), client_socket -> get_socket_port(), resp -> get_unformatted_request().c_str());
		int bytes_count = client_socket -> socket_send(message);
		info("server: send %d bytes to %s:%d", bytes_count, client_socket -> get_socket_host().c_str(), client_socket -> get_socket_port());
	}
}

int get_port(const char* str) {
	if (port_validate(str)) return atoi(str);
	else return -1;
}
int main(int argc, char* argv[]) {
	if (argc < 2) {
		error("you need to provide port");
		return 0;
	}

	int port = get_port(argv[1]);
	if (port == -1) {
		error("incorrect port");
		return 0;
	}
	Socket* socket = new Socket();
	if (socket -> get_socket_fd() < 0) {
		error("creating socket error");
		return 0;
	}
	socket -> configure_addr(port);
	if (socket -> socket_bind() < 0) {
		error("socket bind error");
		return 0;
	}
	if (socket -> socket_listen() < 0) {
		error("socket listen error");
		return 0;
	}
	info("listening on port: %d", port);
	while (true) {
		Socket* client_socket = socket -> socket_accept();
		info("server: connection from %s:%d accepted", client_socket -> get_socket_host().c_str(), client_socket -> get_socket_port());
		thread handler_thread(connection_handler, client_socket);
		handler_thread.detach();
	}
	socket -> ~Socket();
}