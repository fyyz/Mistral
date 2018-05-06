#ifndef _MISTRAL_SERVER_H_INCLUDED_
#define _MISTRAL_SERVER_H_INCLUDED_

namespace mistral
{
	namespace http
	{
		class server
		{
		public:
			server() = default;
			server(const server&) = delete;
			server& operator=(const server&) = delete;
			void add_router(
				const std::u32string &path,
				const std::function<void()> &handle
			);
			void run();
		};
	}
}

#endif
