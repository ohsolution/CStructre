#ifndef _PARSER_H
#define _PARSER_H 1

#include "definition.h"
#include "disassembler.h"

class parser
{
private:
    /* data */
    disassembler * DA;
    vector<string> ret;
public:
    parser(vector <unsigned char> * __buf);
    ~parser(void);
    vector<string> * getret(void);
    vector<int> formatSlice(string __w,int __ty);    
};




#endif /* paser.h */