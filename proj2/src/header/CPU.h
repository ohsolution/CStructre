#ifndef _CPU_H
#define _CPU_H 1

#include "definition.h"
#include "parser.h" 

class CPU
{
private:
    int N;
    int pc;
    string curinst;
    parser * Parser;
    vector <int> reg;

public:
    CPU(int _NumOfInst);
    ~CPU(void);
    bool run(void);
    bool fetch(void);
    vector <int> getinfo(void);
};


#endif /* CPU.h */
