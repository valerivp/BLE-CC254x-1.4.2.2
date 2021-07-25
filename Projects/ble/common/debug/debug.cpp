
extern "C"{
#include "OSAL_memory.h"
#include "npi.h"
#include "stdio.h"
#include "string.h"
}

#include "debug.h"

#if defined(DEBUG_UART) && DEBUG_UART

int DebugStackClass::debug_print_last_line = 0;

Print Serial;

void Print::print(const char* arg){
	DebugPrint(arg);
}
void Print::print(long arg){
	DebugPrint("%ld", arg);
}
/*void Print::print(bool arg){
	DebugPrint("%s", arg ? "TRUE" : "FALSE");
}*/
void Print::print(long arg, int base){
	switch(base){
	case 10: DebugPrint("%ld", arg); break;
	case 16: DebugPrint("%lx", arg); break;
	default: DebugPrint("??"); break;
	}
};
void Print::println(){DebugPrint("\n\r");};


void halUARTCBack(uint8 port, uint8 event){
	//printf("halUARTCBack: %d", (int)event);
	
};


uint8* buf = nullptr;
void InitDebugOutput()
{
	PERCFG |= 0x02;     //USART1 at alt location 2 TX P1.6, RXP1.7
	P1SEL |= 0xc0;       //P1.6, P1.7 as peripheral
	
	//InitUART1();
	NPI_InitTransport(NULL);
	
	buf = (uint8*)osal_mem_alloc(256);
	DebugPrint("\r\n\033c");
}


void DebugPrint(const char* str, ...)
{

	if(!buf)
		InitDebugOutput();
	va_list vl;
	va_start(vl, str);
	
	int len = vsprintf((char*)buf, str, vl);
	va_end(vl);
	
	//Uart1SendString((char*)buf, len);
	NPI_WriteTransport((uint8*)buf, len);
	
	DebugStackClass::debug_print_last_line = 0;
	//printf((char*)buf);
	
}
char *strrchr_cpp(const char * str, int ch){
	return strrchr(str, ch);
}

#endif