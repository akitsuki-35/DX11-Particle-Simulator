/*============================================================
*	@file	 : debug_ostream.h
*	@brief	 : デバッグログ表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/25
*	@updated : 2026/06/02
*============================================================*/
#ifndef DEBUG_OSTREAM_H
#define DEBUG_OSTREAM_H

#include <Windows.h>
#include <sstream>

namespace dOst
{
	class DebugBuf : public	std::basic_stringbuf < char, std::char_traits<char>>
{
public:

	virtual ~DebugBuf() {
		sync();
	}

protected:

	int sync() {
		OutputDebugStringA(str().c_str());
		str(std::basic_string<char>());
		return 0;
	}
};

class DebugOstream : public std::basic_ostream<char, std::char_traits<char>>
{
public:
	DebugOstream() : std::basic_ostream<char,std::char_traits<char>>(new DebugBuf()){}
	~DebugOstream() { delete rdbuf(); }
};
extern DebugOstream dout;
}

#endif // DEBUG_OSTREAM_H