#ifndef _MISTRAL_TYPE_H_INCLUDED_
#define _MISTRAL_TYPE_H_INCLUDED_

namespace mistral
{
	namespace http
	{
		class http_v
		{};
		class http_vbase : public http_v
		{};
		class http_v1 : public http_v
		{};
		class http_v2 : public http_v
		{};

		typedef std::array<unsigned char, http_msg_buffer_length> http_msg_buffer;
	}
}

#endif