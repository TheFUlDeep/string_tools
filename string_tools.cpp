#pragma once
#include <string>
#include <deque>

namespace string_tools
{
    using namespace std;
    
	const auto STRINGNPOS = string::npos;
	
	string& RemoveSymbolFromSides(string &line, const char &symbol, const bool &front = true, const bool &back = true)
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
		return line;
	}
	
	
	string& RemoveSymbol(string &str, const char &symbol, const size_t &startpos = 0, const size_t &endpos = STRINGNPOS)
	{
		if (startpos > endpos) throw exception("wrong startpos and endpos");
		auto pos = str.find(symbol);
		while (pos != STRINGNPOS && pos >= startpos && pos <= endpos)
		{
			const auto strlen = str.length();
			auto curpos = pos + 1;

			//если идут одинаковые символы подряд, то вырезать их сразу вместе
			while (curpos < strlen && str[curpos] == symbol) curpos++;
			str.erase(pos, curpos - pos);
			pos = str.find(symbol);
		}
		return str;
	}
	
	
	//TODO подумать как свести количество erase'ов к минимуму
	//если повезет, то это будет ReplacePattern(str,pattern,"")
	string& RemovePatternFromSides(string &str, const string &pattern, const size_t &startpos = 0, const size_t &endpos = STRINGNPOS)
	{
		if (startpos > endpos) throw exception("wrong startpos and endpos");
	}
	
	
	string Sub(const string &str, const size_t &startpos = 0, const size_t &endpos = STRINGNPOS)
	{
		if (startpos > endpos) throw exception("wrong startpos and endpos");
		if (endpos + 2 > str.length()) return str.substr(startpos);
		else return str.substr(startpos, endpos - startpos + 1);
	}
	
	
	deque<string> StringExplode(const string &str, const string &pattern)
	{
		deque<string> deq;
		const auto patternlen = pattern.length();
		const auto strlen = str.length();
		auto pos = str.find(pattern);
		if (pos == STRINGNPOS)
		{
			deq.push_back(string(str));
		}
		else
		{
			if (pos != 0) deq.push_back(str.substr(0,pos));
			while (pos != STRINGNPOS)
			{				
				//если это последний паттерн, то это конец
				if (strlen - patternlen == pos) break;
				const auto endpos = pos+patternlen;
				const auto nextpos = str.find(str,endpos);
				if (nextpos == STRINGNPOS)
				{
					deq.push_back(str.substr(endpos));
					break;
				}
				else
				{
					deq.push_back(str.substr(endpos, nextpos - endpos));
				}
				pos = nextpos;
			}
		}
		return deq;
	}
	
	
	string GSub(const string &str1, const string &oldpattern, const string &newpattern, const size_t &startpos = 0, const size_t &endpos = STRINGNPOS)
	{
		if (startpos > endpos) throw exception("wrong startpos and endpos");
		auto str = str1;
		const auto oldpatternlen = oldpattern.length();
		auto startfind = str.find(oldpattern);
		while (startfind != STRINGNPOS && startfind >= startpos && (startfind+oldpatternlen-1) <= endpos)
		{
			str.replace(startfind, oldpatternlen, newpattern);
			startfind = str.find(oldpattern);
		}
		return str;
	}
	
	string DequeToString(const deque<string> &deq, const string &pattern = "")
	{
		string res = "";
		for (auto str : deq)
		{
			res += (str + pattern);
		}
		const auto patternlen = pattern.length();
		res.erase(res.length() - patternlen,patternlen);
		return res;
	}
}