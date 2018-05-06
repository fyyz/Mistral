#include "mistral_header.h"

mistral::http::session::session
(
	std::shared_ptr<boost::asio::io_service>      io_service_ptr,
	boost::asio::ip::tcp::socket                  socket
)
:io_service_ptr(io_service_ptr)
,_socket(std::move(socket))
{
}

void mistral::http::session::start()
{
	do_read();
}

void mistral::http::session::do_read()
{
	auto self(shared_from_this());
	_socket.async_read_some(
		boost::asio::buffer(_http_msg_buffer),
		[this, self](boost::system::error_code ec, std::size_t length)
		{
			if (ec)
			{
				return;
			}

			_request_parser.append_msg(_http_msg_buffer, length);

			if (!_request_parser.do_parse())
			{
				return;
			}

			if (!_request_parser.msg_end())
			{
				do_read();
			}
			else
			{
				do_write();
			}
		}
	);
}

void mistral::http::session::do_write()
{
	auto self(shared_from_this());
	router::get_instance().run_handle(_request_parser.get_request(), _response_build.get_response());
	_http_response_msg = _response_build.complete_msg();
	boost::asio::async_write(
		_socket,
		boost::asio::buffer(_http_response_msg, _http_response_msg.size()),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (ec)
			{
				return;
			}
		}
	);
}

void mistral::http::session::do_read_handle()
{
}

void mistral::http::session::do_write_handle()
{
}
