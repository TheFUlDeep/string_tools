#pragma once
#include <string>
#include <deque>

//TODO поменять эксэпшны на свапы

namespace string_tools
{
    using namespace std;
    
	const auto STRINGNPOS = string::npos;
	
	string RemoveSymbolFromSides(const string &line1, const char &symbol, const bool &front = true, const bool &back = true)
	{
		if (line1.length() == 0) return "";
		auto line = line1;
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
	
	
	string RemoveSymbol(const string &str1, const char &symbol, const size_t &startpos = 0, const size_t &endpos = STRINGNPOS)
	{
		if (str1.length() == 0) return "";
		if (startpos > endpos) throw exception("wrong startpos and endpos");
		auto str = str1;
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
	
	
	string RemovePatternFromSides(const string &str1, const string &pattern, const bool &front = true, const bool &back = true)
	{
		if (str1.length() == 0) return "";
		if (startpos > endpos) throw exception("wrong startpos and endpos");
		auto str = str1;
		const auto patternlen = pattern.length();
		
		if (front)
		{
			while (str.find(pattern) == 0)
			{
				size_t newpos = patternlen;
				//не выбросится ли исключение, если newpos будет за пределами стринга?//TODO проверить
				while (str.find(pattern, newpos) == newpos) newpos += patternlen;
				str.erase(0,newpos)
			}
		}
		
		if (back)
		{
			size_t newpos = str.length() - patternlen;
			while (str.rfind(pattern) == newpos)
			{
				//не выбросится ли исключение, если newpos - 1 будет за пределами стринга?//TODO проверить
				while (str.rfind(pattern, newpos - 1) == newpos - patternlen) newpos -= patternlen;
				str.erase(newpos);
				newpos--;
			}
		}
		return str;
	}
	
	
	string Sub(const string &str, const size_t &startpos = 0, const size_t &endpos = STRINGNPOS)
	{
		if (str.length() == 0) return "";
		if (startpos > endpos) throw exception("wrong startpos and endpos");
		if (endpos + 2 > str.length()) return str.substr(startpos);
		else return str.substr(startpos, endpos - startpos + 1);
	}
	
	
	deque<string> StringExplode(const string &str, const string &pattern)
	{
		if (str.length() == 0) return "";
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
		if (str1.length() == 0) return "";
		if (startpos > endpos) throw exception("wrong startpos and endpos");
		auto str = str1;
		if (oldpattern == newpattern) return str;
		const auto oldpatternlen = oldpattern.length();
		auto startfind = str.find(oldpattern);
		while (startfind != STRINGNPOS && startfind >= startpos && startfind + oldpatternlen - 1 <= endpos)
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
	
	string SwapParts(const string &str, const size_t &startpos1, const size_t &endpos1, const size_t &startpos2, const size_t &endpos2)
	{
		const auto strlen = str.length();
		if (strlen == 0) return "";
		
		if (startpos1 > endpos1 || startpos2 > endpos2 || endpos1 >= startpos2) throw exception("wrong startpos and endpos");
		
		string prev = "";
		if (startpos1 != 0) prev = Sub(str, 0, startpos1 - 1);
		
		string post = "";
		if (endpos2 < strlen - 1) prev = Sub(str, endpos2 + 1);
		
		string between = "";
		if (startpos2 - endpos1 > 1) between = Sub(endpos1 + 1, startpos2 - 1);
		
		auto segment1 = Sub(str, startpos1, endpos1);
		auto segment2 = Sub(str, startpos2, endpos2);
		
		return (prev + segment2 + between + segment1 + post);
	}
}