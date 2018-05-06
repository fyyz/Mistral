#include "mistral_header.h"

void mistral::http::server::add_router(
	const std::u32string &path,
	const std::function<void()> &handle
)
{
	router::get_instance().add(path, handle);
}

void mistral::http::server::run()
{
	std::shared_ptr<boost::asio::io_service> io_service_ptr = std::make_shared<boost::asio::io_service>();
	listener listener(io_service_ptr,"0.0.0.0",8000);
	io_service_ptr->run();
}