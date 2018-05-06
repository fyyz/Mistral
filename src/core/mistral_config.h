#ifndef _MISTRAL_CONFIG_H_INCLUDED_
#define _MISTRAL_CONFIG_H_INCLUDED_

const std::string   server_name                    = "mistral";
const std::string   server_version                 = "dev";

const std::uint16_t server_listen_port             = 8000;

//const std::size_t   http_msg_buffer_length         = 4 * 1024;
const std::size_t   http_msg_buffer_length         = 4;
const std::size_t   http_msg_first_line_max_length = 8 * 1024;
const std::size_t   http_msg_header_max_length     = 16 * 1024;
const std::size_t   http_msg_body_max_length       = 16 * 1024 * 1024;

#endif
