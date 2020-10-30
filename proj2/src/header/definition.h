#ifndef _DEFINITION_H
#define _DEFINITION_H 1


/* Standard Libary header */
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <unordered_map>

using namespace std;

/* OPCODE */
#define ARITHI 1
#define LOADI 2
#define BRANCH 3
#define LOADSTORE 4
#define JUMP 5

 /* FUNCTCODE */
#define ARITH 1
#define DIVMUL 2
#define SHIFT 3
#define SHIFTV 4
#define JUMPR 5
#define MOVEFROM 6
#define MOVETO 7
#define SYSTEMCALL 8
#define JUMPLR 9

struct info
{
    string is;
    int ty;
};



#endif /* definition.h */