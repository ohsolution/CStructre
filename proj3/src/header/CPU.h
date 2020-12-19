#ifndef _CPU_H
#define _CPU_H 1

#include "definition.h"
#include "pipe.h" 

class PIPE_IF;
class PIPE_ID;
class PIPE_EX;
class PIPE_MEM;
class PIPE_WB;
class PIPE;

class CPU
{
public:
    PIPE_IF * pif;
    PIPE_ID * pid;
    PIPE_EX * pex;
    PIPE_MEM * pmem;
    PIPE_WB * pwb;

    vector <int> reg;
    int pc,checksum,N,lpc;
    
    CPU(int _NumOfCycle);
    ~CPU(void);
    void run(void);    
    vector <int> getinfo(void);
    void addBubble(PIPE *p1,PIPE *p2);
    void showinfo(INST it);
    void showpipe(void);
    //bool fetch(void);
};


#endif /* CPU.h */
