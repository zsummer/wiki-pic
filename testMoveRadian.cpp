#ifdef WIN32
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <windows.h>
#include <DbgHelp.h>
#include <string>
#pragma comment(lib, "Dbghelp")
#else
#include <execinfo.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <chrono>
#include <string.h>
#include <atomic>
#include <memory>
#include <functional>
using namespace std;

#define PI 3.14159265F
struct EPoint //point  
{
    float x;
    float y;
    EPoint()
    {
        x = 0.0;
        y = 0.0;
    }
};

inline EPoint moveTo(EPoint org, float radian, float distance)
{
    EPoint pt;
    pt.x = cos(radian) * distance;
    pt.y = sin(radian) * distance;
    pt.x += org.x;
    pt.y += org.y;
    return pt;
}

inline float getRadian(EPoint org, EPoint dst)
{
    return atan((dst.y - org.y) / (dst.x - org.x));
}


int main(int argc, char *argv[])
{
    float radian[] = { PI / 3, PI / 2, PI / 3 * 2, PI, PI + PI / 3, PI + PI / 2, PI + PI / 3 * 2, PI * 2 };
    for (int i = 0;i<sizeof(radian)/sizeof(float) ; i++)
    {
        auto dst = moveTo(EPoint(), radian[i], 100);
        cout << "face = " << radian[i] / 2 / PI * 360 << ", radian=" << radian[i] << ", x=" << dst.x << ", y=" << dst.y << endl;
        cout << "atan=" << getRadian(EPoint(), dst) << endl;
    }
    return 0;
}

/*
g++ stack.cpp -g -O0
gdb info line * 0x40000000
google coredumper
*/
