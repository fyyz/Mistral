#include "mistral_header.h"

mistral::http::session_v1::session_v1
(
	std::shared_ptr<boost::asio::io_service>      io_service_ptr,
	boost::asio::ip::tcp::socket                  socket
)
:io_service_ptr(io_service_ptr)
,_socket(std::move(socket))
{
}

void mistral::http::session_v1::start()
{
	do_read();
}

void mistral::http::session_v1::do_read()
{
	auto self(shared_from_this());
	_socket.async_read_some(
		boost::asio::buffer(_request_v1_extra.get_request().buffer()),
		[this, self](boost::system::error_code ec, std::size_t length)
		{
			if (ec)
			{
				return;
			}

			_request_v1_extra.append_msg(_request_v1_extra.get_request().buffer(), length);

			if (!_request_v1_extra.do_parse())
			{
				return;
			}

			if (!_request_v1_extra.msg_end())
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

void mistral::http::session_v1::do_write()
{
	auto self(shared_from_this());
	router::get_instance().run_handle(_request_v1_extra.get_request(), _response_v1_extra.get_response());
	_response_v1_extra.complete_msg();
	boost::asio::async_write(
		_socket,
		boost::asio::buffer
		(
			_response_v1_extra.get_response().msg_body(),
			_response_v1_extra.get_response().msg_body().size()
		),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (ec)
			{
				return;
			}
		}
	);
}

