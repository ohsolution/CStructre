#ifndef _PARSER_H
#define _PARSER_H 1

#include "definition.h"
#include "disassembler.h"

class parser
{
private:
    /* data */
    disassembler * DA;
    //vector<string> ret;
public:
    parser(void);
    ~parser(void);
    //vector<string> * getret(void);
    vector<int> formatSlice(string __w,int __ty);    
    static void save_ISM(vector <unsigned char> * _buff);
    vector <int> parsing(string _inst);
};


#endif /* paser.h */