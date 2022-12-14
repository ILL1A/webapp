#include <iostream> 
#include <string>
#include <thread>
#include "include/logger.h"
#include "include/comparator.h"
#include "include/socket.h"
#include "include/exchange.h"

using namespace std;
using namespace logger;
using namespace comparator;
using namespace http_request;

void send_response(Response* response, Socket* client_socket) {
	string str_response = response -> generate_str();
	info("body: %s", response -> get_response_body().c_str());
	info("generated response: %s", str_response.c_str());
	int bytes_count = client_socket -> socket_send(str_response);
	info("server: send %d bytes to %s:%d", bytes_count, client_socket -> get_socket_host().c_str(), client_socket -> get_socket_port());
}

void connection_handler(Socket* client_socket) {
	Request* resp = new Request();
	while ((resp = client_socket -> socket_read()) -> get_request_length() > 0) {
		resp -> format();
		info("server: got message from %s:%d: %d bytes", client_socket -> get_socket_host().c_str(), client_socket -> get_socket_port(), resp -> get_unformatted_request().size());
		info("route: %s", resp -> get_request_route().c_str());
		string route = resp -> get_request_route();
		if (check_start("/static/styles", route)) {
			route.erase(0, 1);
			Response* response = new Response();
			response -> add_main(resp -> get_http_version(), "200 OK");
			response -> add_body(render_file(route));
			response -> add_header("Content-Type", "text/css");
			response -> add_header("Content-Length", to_string((response -> get_response_body()).size()));
			send_response(response, client_socket);
		} else if (check_start("/static/scripts", route)) {
			route.erase(0, 1);
			Response* response = new Response();
			response -> add_main(resp -> get_http_version(), "200 OK");
			response -> add_body(render_file(route));
			response -> add_header("Content-Type", "text/javascript");
			response -> add_header("Content-Length", to_string((response -> get_response_body()).size()));
			send_response(response, client_socket);
		} else if (route == "/") {
			Response* response = new Response();
			response -> add_main(resp -> get_http_version(), "200 OK");
			response -> add_body(render_file("templates/index.html"));
			response -> add_header("Content-Type", "text/html");
			response -> add_header("Content-Length", to_string((response -> get_response_body()).size()));
			send_response(response, client_socket);
		} else {
			Response* response = new Response();
			response -> add_main(resp -> get_http_version(), "404 Not Found");
			response -> add_body(render_file("templates/404.html"));
			response -> add_header("Content-Type", "text/html");
			response -> add_header("Content-Length", to_string((response -> get_response_body()).size()));
			send_response(response, client_socket);
		}
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