#ifndef _MISTRAL_SESSION_HPP_INCLUDED_
#define _MISTRAL_SESSION_HPP_INCLUDED_

namespace mistral
{
	namespace http
	{
		class session : public std::enable_shared_from_this<session>
		{
		public:
			session() = delete;
			session(const session&) = delete;
			session(
				std::shared_ptr<boost::asio::io_service>      io_service_ptr,
				boost::asio::ip::tcp::socket                  socket
			);
			void start();

		private:
			std::shared_ptr<boost::asio::io_service>      io_service_ptr;
			http_msg_buffer                               _http_msg_buffer;
			std::string                                   _http_response_msg;
			boost::asio::ip::tcp::socket                  _socket;
			request_parser                                _request_parser;
			response_build                                _response_build;

			void do_read();
			void do_write();
			void do_read_handle();
			void do_write_handle();
		};
	}
}

#endif