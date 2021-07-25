/*
Streaming.h - Arduino library for supporting the << streaming operator
Copyright (c) 2010-2012 Mikal Hart.  All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

class Print{
public:
	void print(const char* arg);
//	void print(bool arg);
	void print(long arg);
	void print(long arg, int base);
	void println();
};

extern Print Serial;



// Generic template
template<class T> 
inline Print &operator <<(Print &stream, T arg) 
{ stream.print(arg); return stream; }

struct _BASED 
{ 
  long val; 
  int base;
  _BASED(long v, int b): val(v), base(b) 
  {}
};


#define _BYTE(a)    _BASED(a, BYTE)

#define _HEX(a)     _BASED(a, HEX)
#define _DEC(a)     _BASED(a, DEC)
//#define _BIN(a)     _BASED(a, BIN)

// Specialization for class _BASED
// Thanks to Arduino forum user Ben Combee who suggested this 
// clever technique to allow for expressions like
//   Serial << _HEX(a);

inline Print &operator <<(Print &obj, const _BASED &arg)
{ obj.print(arg.val, arg.base); return obj; } 


// Specialization for enum _EndLineCode
// Thanks to Arduino forum user Paul V. who suggested this
// clever technique to allow for expressions like
//   Serial << "Hello!" << endl;

enum _EndLineCode { endl };

inline Print &operator <<(Print &obj, _EndLineCode arg) 
{ obj.println(); return obj; }


#ifndef _DEBUG_H_
#define _DEBUG_H_



#if defined(DEBUG_UART) && DEBUG_UART

char *strrchr_cpp(const char *, int);


class DebugStackClass {
	
	const char * _file;
	const char * _func;
public:
	DebugStackClass(const char * file, const char * func, int l) {
		_file = strrchr_cpp(file, '\\');
		_func = func;
		Serial << (">Begin: ") << _file << "(" << l << ")" << _func << endl;
		
	};
	~DebugStackClass() {
		Serial << ("<End:   ") << _file << ":" << _func << endl;
		
	};
	
	static int debug_print_last_line;

};

#define DEBUG_STACK() DebugStackClass __DebugStack(__FILE__, __FUNCTION__, __LINE__)
#define DEBUG_STACK_PRINT(x) DebugStackClass __DebugStack(__FILE__, __FUNCTION__, __LINE__); Serial << x << endl

#define DEBUG_PRINT(x) Serial << strrchr_cpp((__FILE__), '\\') << "(" << __LINE__ << ")" << __FUNCTION__  << ": " << x << endl


//#define DEBUG_STATE_PRINT(x) Serial << (DebugStackClass::debug_print_last_line == __LINE__ ? "\033[1F\033[2K" : "") << strrchr_cpp((__FILE__), '\\') << "(" << __LINE__ << ")" << __FUNCTION__  << ": " << x << endl; DebugStackClass::debug_print_last_line = __LINE__
#define DEBUG_STATE_PRINT(x) Serial << (DebugStackClass::debug_print_last_line == __LINE__ ? "\033[1F\033[2K" : "") << x << endl; DebugStackClass::debug_print_last_line = __LINE__

//void InitDebugOutput();
void DebugPrint(const char* str, ...);

#else

#define DEBUG_STACK() 
#define DEBUG_STACK_PRINT(x) 

#define DEBUG_PRINT(x)

#define DebugPrint(...)

#endif




#endif