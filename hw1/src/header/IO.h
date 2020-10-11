#ifndef _IO_H
#define _IO_H 1

#include "definition.h"

class IO
{
private:
    /* data */
public:
    vector <unsigned char> buf;
    IO(char * __arg);
    ~IO(void);
    
};

#endif /* IO.h */