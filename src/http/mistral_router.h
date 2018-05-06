#ifndef _MISTRAL_ROUTER_H_INCLUDED_
#define _MISTRAL_ROUTER_H_INCLUDED_

namespace mistral
{
	namespace http
	{
		class router_item
		{
		public:
			router_item() = delete;
			router_item(const router_item&) = delete;
			router_item& operator=(const router_item&) = delete;
			explicit router_item
			(
				const std::u32string  sub_path,
				std::function<void()> handle = nullptr
			);
			std::u32string sub_path() const;

			std::function<void()> handle() const;
			void handle(const std::function<void()> &handle);

			std::shared_ptr<router_item> child() const;
			void child(std::shared_ptr<router_item> router_item_ptr);
			
			std::shared_ptr<router_item> sibling() const;
			void sibling(std::shared_ptr<router_item> router_item_ptr);
		private:
			const std::u32string         _sub_path;
			std::function<void()>        _handle  = nullptr;
			std::shared_ptr<router_item> _child   = nullptr;
			std::shared_ptr<router_item> _sibling = nullptr;
		};

		class router
		{
		public:
			static router& get_instance()
			{
				static mistral::http::router instance;
				return instance;
			}

			void add(const std::u32string &path,const std::function<void()> &handle);
			void run_handle(const request& _request, response& _response);
		private:

			router();
			std::shared_ptr<router_item> root = nullptr;

			std::vector<std::u32string> split_path(const std::u32string &path);
		};
	}
}

#endif
