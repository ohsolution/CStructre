#include "header/IO.h"
#include "header/definition.h"

inline char conveter(int x){return x>=10 ? 'a'+(x-10) : '0'+x;}

string padding(string str,int sz,char ch)
{
    while(str.size()<sz) str += ch;
    return str;
}

string dec_to_hex(int x)
{
    string ret="";

    while(x)
    {
        ret.push_back(conveter(x&15));
        x>>=4;
    }

    padding(ret,8,'0');

    ret += "x0";
    
    reverse(ret.begin(),ret.end());
    return ret;
}



IO::IO(char * arg)
{
    ifstream input(arg,ios::binary);
    buf = vector <unsigned char>(istreambuf_iterator<char>(input),{});
}

IO::~IO(void)
{
    buf.clear();
}

vector <unsigned char> * IO::getbuf(void)
{
    return &buf;
}

void IO::output(vector <string> argv,vector <int> * reg)
{
    
}