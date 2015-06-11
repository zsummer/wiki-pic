#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using namespace std;

void tracebackHandler()
{
	void *stack[200];
	size_t size = backtrace(stack, 200);
	char **stackSymbol = backtrace_symbols(stack, size);
	for (size_t i =0; i < size && stackSymbol != NULL; i++)
	{
		std::cout << "bt[" << i << "] " << stackSymbol[i] << std::endl;
	}
	free(stackSymbol);
}


void test(int a)
{
	tracebackHandler();
}
int main(int argc, char *argv[])
{
	test(1);	
	
	return 0;
}

/*
    g++ stack.cpp -g -O0
    gdb info line * 0x40000000
    google coredumper
*/