#include "mistral_header.h"

mistral::http::router_item::router_item
(
	const std::u32string sub_path,
	const std::function<void()> handle
)
:_sub_path(sub_path)
,_handle(handle)
{
}

std::u32string mistral::http::router_item::sub_path() const
{
	return _sub_path;
}

std::function<void()> mistral::http::router_item::handle() const
{
	return _handle;
}

void mistral::http::router_item::handle(const std::function<void()> &handle)
{
	_handle = handle;
}

std::shared_ptr<mistral::http::router_item> mistral::http::router_item::child() const
{
	return _child;
}

void mistral::http::router_item::child(std::shared_ptr<mistral::http::router_item> router_item_ptr)
{
	_child = router_item_ptr;
}

std::shared_ptr<mistral::http::router_item> mistral::http::router_item::sibling() const
{
	return _sibling;
}

void mistral::http::router_item::sibling(std::shared_ptr<mistral::http::router_item> router_item_ptr)
{
	_sibling = router_item_ptr;
}

mistral::http::router::router()
:root(std::make_shared<router_item>(U""))
{
}

void mistral::http::router::add(const std::u32string &path,const std::function<void()> &handle)
{
	if (path.size() == 0 || path.at(0) != U'/')
	{
		// EXIT LOG
	}

	std::vector<std::u32string> sub_path_vec = split_path(path);
	std::shared_ptr<router_item> router_item_ptr = root;

	for (auto &sub_path : sub_path_vec)
	{
		if (router_item_ptr->child() == nullptr)
		{
			std::shared_ptr<router_item> next_router_item_ptr = std::make_shared<router_item>(sub_path);
			router_item_ptr->child(next_router_item_ptr);
			router_item_ptr = router_item_ptr->child();
		}
		else
		{
			router_item_ptr = router_item_ptr->child();
			while (router_item_ptr->sub_path() != sub_path)
			{
				if (router_item_ptr->sibling() == nullptr)
				{
					std::shared_ptr<router_item> next_router_item_ptr = std::make_shared<router_item>(sub_path);
					router_item_ptr->sibling(next_router_item_ptr);
				}
				router_item_ptr = router_item_ptr->sibling();
			}
		}
	}

	if (router_item_ptr->handle() != nullptr)
	{
		// EXIT LOG
	}

	router_item_ptr->handle(handle);
}

void mistral::http::router::run_handle(const mistral::http::request& _request, mistral::http::response& _response)
{
	_response.status_code(404);
	_response.phrase("Not Found");
	_response.error_msg_body();
}

std::vector<std::u32string> mistral::http::router::split_path(const std::u32string &path)
{
	std::u32string temp;
	std::vector<std::u32string> sub_path_vec;
	for (std::size_t i = 0; i != path.size(); i++)
	{
		temp.push_back(path.at(i));
		if (i + 1 != path.size() && path.at(i+1) == U'/')
		{
			sub_path_vec.push_back(temp);
			temp.clear();
		}
	}
	sub_path_vec.push_back(temp);
	return sub_path_vec;
}
