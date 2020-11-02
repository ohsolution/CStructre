#include "header/parser.h"
#include "header/definition.h"
#include "header/memory.h"

string p_buf(unsigned char t)
{
    string ret;

    for(int i= 7; i >-1; --i)
    {
        int bit = 1<<i;

        if(t & bit) ret.push_back('1');
        else ret.push_back('0');
    }

    return ret;
}
parser::parser(void)
{
    DA = new disassembler();
}

void parser::save_ISM(vector <unsigned char> * buff)
{
    vector <unsigned char> & buf = *buff;
    
    for(int i=0;i < buf.size();i+=4)
    {        
        string binary = p_buf(buf[i]) + p_buf(buf[i+1]) + p_buf(buf[i+2]) + p_buf(buf[i+3]);
        ISM[(i>>2)] = binary;        
    }

    return;   
}

parser::~parser()
{
    delete DA;
}
 
vector <int> parser::parsing(string inst)
{
    int type = stoi(inst.substr(0,6),nullptr,2);
    return formatSlice(inst,type);
}

vector <int> parser::formatSlice(string w,int ty)
{
    vector <int> ret;
    ret.push_back(ty);

    if(!ty)
    {
        for(int i=0;i<4;++i) ret.push_back(stoi(w.substr(6+5*i,5),nullptr,2));
        ret.push_back(stoi(w.substr(26,6),nullptr,2));
    }
    else if(ty==2 || ty ==3) ret.push_back(stoi(w.substr(6,26),nullptr,2));
    else 
    {
        for(int i=0;i<2;++i) ret.push_back(stoi(w.substr(6+5*i,5),nullptr,2));
        int temp = stoi(w.substr(17,15),nullptr,2);
        if(w[16]=='1') temp -= 1<<15;
        ret.push_back(temp);
    }   

    return ret;
}

