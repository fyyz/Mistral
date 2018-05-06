#include "mistral_header.h"

void hello_page()
{

}

int main()
{
	mistral::http::server http_server;
	http_server.add_router(U"/", hello_page);
	http_server.add_router(U"/hello", hello_page);
	http_server.add_router(U"/hello/aaa/bbb/ccc", hello_page);
	http_server.add_router(U"/hello/aaa/bbb/ccc/ddd/", hello_page);
	http_server.add_router(U"/about", hello_page);
	http_server.add_router(U"/post/1", hello_page);
	http_server.add_router(U"/post/2", hello_page);
	http_server.add_router(U"/commit/all/user1", hello_page);
	http_server.run();
}