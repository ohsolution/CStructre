#ifndef _PIPE_H
#define _PIPE_H 1

#include "definition.h"
#include "CPU.h"
#include "parser.h"

class CPU;

class PIPE
{
protected:    
    CPU * cpu;
    INST inst;
    
public:
    bool vaild;
    PIPE(CPU * _cpu);
    void Set_inst(INST _inst);
    //~PIPE();
};

class PIPE_IF : public PIPE
{
private:
    string instr; 
public:
    PIPE_IF(CPU * _cpu);
    string exec();
};

class PIPE_ID : public PIPE 
{
private:
    parser * Parser;
    string instr;
public:
    PIPE_ID(CPU * _cpu);
    ~PIPE_ID();
    INST exec();
    void Set_instr(string _instr);

};

class PIPE_EX : public PIPE 
{
public:
    PIPE_EX(CPU * _cpu);
    INST exec();
};

class PIPE_MEM : public PIPE 
{
public:
    PIPE_MEM(CPU * _cpu);
    INST exec();
};

class PIPE_WB : public PIPE 
{
public:
    PIPE_WB(CPU * _cpu);
    void exec();
};



#endif /* pipe.h */