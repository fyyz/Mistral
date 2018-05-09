#ifndef _MISTRAL_RESPONSE_H_INCLUDED_
#define _MISTRAL_RESPONSE_H_INCLUDED_

namespace mistral
{
	namespace http
	{
		class response
		{
		public:
			void          status_code(std::uint16_t code);
			void          phrase(std::string phrase);
			void          msg_body(std::string msg_body);

			const std::uint16_t & status_code() const;
			const std::string   & phrase() const;
			const std::string   & msg_body() const;

			void          error_msg_body();
		private:
			std::uint16_t _status_code = 0;
			std::string   _phrase;
			std::string   _msg_body;
		};

		
		class response_v1_extra
		{
		public:
			response_v1_extra() = default;
			void         complete_msg();
			response&    get_response();
		private:
			response     _response;
		};
	}
}


#endif