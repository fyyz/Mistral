#ifndef _MISTRAL_SESSION_H_INCLUDED_
#define _MISTRAL_SESSION_H_INCLUDED_

namespace mistral
{
	namespace http
	{
		class basic_session
		{
		public:
			virtual void start() = 0;
		protected:
			virtual void do_read()  = 0;
			virtual void do_write() = 0;
		};

		class session_v1 : public basic_session, public std::enable_shared_from_this<session_v1>
		{
		public:
			session_v1() = delete;
			session_v1(const session_v1&) = delete;
			session_v1(
				std::shared_ptr<boost::asio::io_service>      io_service_ptr,
				boost::asio::ip::tcp::socket                  socket
			);
			virtual void start();
		private:
			std::shared_ptr<boost::asio::io_service> io_service_ptr;
			boost::asio::ip::tcp::socket             _socket;

			request_v1_extra                         _request_v1_extra;
			response_v1_extra                        _response_v1_extra;

			virtual void do_read();
			virtual void do_write();
		};
	}
}

#endif
