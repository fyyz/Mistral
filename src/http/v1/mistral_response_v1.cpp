#include "mistral_header.h"

void mistral::http::response::status_code(std::uint16_t code)
{
	_status_code = code;
}

void mistral::http::response::phrase(std::string phrase)
{
	_phrase = phrase;
}

void mistral::http::response::msg_body(std::string msg)
{
	_msg_body = msg;
}

const std::uint16_t & mistral::http::response::status_code() const
{
	return _status_code;
}

const std::string & mistral::http::response::phrase() const
{
	return _phrase;
}

const std::string & mistral::http::response::msg_body() const
{
	return _msg_body;
}

void mistral::http::response::error_msg_body()
{
	_msg_body.clear();
	_msg_body.append(std::to_string(_status_code))
		.append(" ")
		.append(_phrase);
}

mistral::http::response& mistral::http::response_v1_extra::get_response()
{
	return _response;
}

void mistral::http::response_v1_extra::complete_msg()
{
	std::string result;
	result.append("HTTP/1.1 ")
		.append(std::to_string(_response.status_code()))
		.append(" ")
		.append(_response.phrase())
		.append("\r\n");
	result.append("Connection: close\r\n");
	result.append("Server: mistral/0.0.1\r\n");
	result.append("Content-Type: text/plain\r\n");
	result.append("Content-Length: ").append(std::to_string(_response.msg_body().length())).append("\r\n");
	result.append("\r\n");
	result.append(_response.msg_body());

	_response.msg_body(result);
}
