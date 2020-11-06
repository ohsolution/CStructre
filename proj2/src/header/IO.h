#ifndef _IO_H
#define _IO_H 1

#include "definition.h"

class IO
{
private:
    /* data */
    vector <unsigned char> buf;
public:
    
    IO(char * __arg);
    ~IO(void);
    vector <unsigned char> * getbuf(void);
    void print(vector<string> * __output);
    void output(vector <string> _argv,int _tp,vector <int> _reg);    
};

#endif /* IO.h */