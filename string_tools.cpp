#pragma once
#include <string>

namespace string_tools
{
	const auto STRINGNPOS = string::npos;
	
	void RemoveSymbolFromStringSides(string &line, const char symbol, const bool front = true, const bool back = true)
	{
		if (front)
		{
			while (line.front() == symbol)
			{
				const auto strlen = line.length();
				size_t len = 1;

				//если идут пропуски подряд, то вырезать их сразу вместе
				while (len < strlen && line[len] == symbol) len++;
				line.erase(0, len);
			}
		}

		if (back)
		{
			while (line.back() == symbol)
			{
				const auto strlen = line.length();
				auto pos = strlen - 2;

				//если идут пропуски подряд, то вырезать их сразу вместе
				while (pos < strlen && line[pos] == symbol) pos--;
				pos++;
				line.erase(pos, strlen - pos);
			}
		}
	}
	
	void RemoveSymbolFromString(string &str, const char symbol)
	{
		auto pos = str.find(symbol);
		while (pos != STRINGNPOS)
		{
			const auto strlen = str.length();
			auto curpos = pos + 1;

			//если идут одинаковые символы подряд, то вырезать их сразу вместе
			while (curpos < strlen && str[curpos] == symbol) curpos++;
			str.erase(pos, curpos - pos);
			pos = str.find(symbol);
		}
	}
}

