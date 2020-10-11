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
};

#endif /* IO.h */