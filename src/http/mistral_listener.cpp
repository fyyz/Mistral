#include "mistral_header.h"

mistral::http::listener::listener
(
	std::shared_ptr<boost::asio::io_service> io_service_ptr,
	std::string                              ip,
	std::uint16_t                            port
)
:io_service_ptr(io_service_ptr)
,_acceptor(*io_service_ptr, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), port))
,_socket(*io_service_ptr)
{
	do_accept();
}

void mistral::http::listener::do_accept()
{
	_acceptor.async_accept
	(
		_socket,
		[this](boost::system::error_code ec)
		{
			if (!ec)
			{
				std::make_shared<session_v1>(io_service_ptr, std::move(_socket))->start();
			}
			do_accept();
		}
	);
}