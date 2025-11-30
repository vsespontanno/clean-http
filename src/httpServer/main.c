#include <stdio.h>
#include <string.h>

#include "extclib/http.h"

void index_page(int conn, HTTPReq *request)

int main(void) {
	HTTP *serve = new_http("127.0.0.1:8080");
	handle_http(serve, "/", index_page);
	handle_http(serve, "/about", about_page);
	
	listen_http(serve);
	free_http(serve);
}

void index_page(int conn, HTTPReq *request) {
	if(strcmp(request->path, "/")) {
		parsehtml_http(conn, "page404.html");
		return;
	}
	parsehtml_http(conn, "index.html");
}

void about_page(int conn, HTTPReq *request) {
	if(strcmp(request->path, "/about")) {
		parsehtml_http(conn, "page404.html");
		return;
	}
	parsehtml_http(conn, "about.html");
}