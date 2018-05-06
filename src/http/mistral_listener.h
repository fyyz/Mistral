#ifndef _MISTRAL_LISTENER_H_INCLUDED_
#define _MISTRAL_LISTENER_H_INCLUDED_

namespace mistral
{
	namespace http
	{
		class listener : public std::enable_shared_from_this<listener>
		{
		public:
			listener() = delete;
			listener(const listener&) = delete;
			listener
			(
				std::shared_ptr<boost::asio::io_service> io_service_ptr,
				std::string                              ip,
				std::uint16_t                            port
			);
		private:
			std::shared_ptr<boost::asio::io_service>      io_service_ptr;
			boost::asio::ip::tcp::socket                  socket;
			boost::asio::ip::tcp::acceptor                acceptor;
			std::string                                   ip;
			std::uint16_t                                 port;

			void do_accept();
		};
	}
}

#endif