#ifndef _MISTRAL_LOG_H_INCLUDED_
#define _MISTRAL_LOG_H_INCLUDED_

namespace mistral
{
	class log
	{
	public:
		static log& getInstance()
		{
			static log instance;
			return instance;
		}
		void push_back(const std::u32string &log_message);
	private:
		std::queue<std::u32string> log_queue;
		std::ofstream log_file;
		std::u32string pop_front();
		std::uint8_t log_level;

		void write();
	};
}

#endif
