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
#include <bits/stdc++.h>
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

/* PRINTMODE */
#define NOPRINT 1
#define REGPRINT 2
#define MEMPRINT 3


struct info
{
    string is;
    int ty;
};


enum TYPE
{
    DEFAULT,
    RTYPE ,
    ITYPE,
    JTYPE
};

struct INST
{
    TYPE tp = DEFAULT;
    bool regWrite=false;
    int code=0;
    int *rs;
    int *rd;
    int *rt;
    int rsv=0;
    int rdv=0;
    int rtv=0;
    int wval = 0;
    int imm,uimm,shamt;
    int address;
};




#endif /* definition.h */