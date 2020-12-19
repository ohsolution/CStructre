#include "header/IO.h"
#include "header/definition.h"
#include "header/memory.h"

inline char conveter(unsigned int x){return x>=10 ? 'a'+(x-10) : '0'+x;}
inline int conveter(char x){return x<='9' ? x-'0' : (x>='a' ? (x-'a'+10):(x-'A'+10));}

void padding(string * str,int sz,char ch)
{
    while(str->size()<sz) *str += ch;
    return;
}

string dec_to_hex(unsigned int x)
{
    string ret="";

    while(x)
    {
        ret.push_back(conveter(x&15));
        x>>=4;
    }

    padding(&ret,8,'0');

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

void IO::output(vector <string> argv,int tp,vector <int> regpc)
{
    if(tp==NOPRINT) return;    

    if(tp==REGPRINT)
    {
        cout << "Checksum: " << dec_to_hex(regpc[33])<<"\n";
        for(int i=0;i<32;++i) cout << regname[i] <<": "<<dec_to_hex(regpc[i])<<"\n";
        cout << "PC: " << dec_to_hex(regpc[32]) <<"\n";
        return;
    }

    if(tp == MEMPRINT)
    {
        int base = 0;
        int c= 0;        
        for(int i=9;i>1;--i,++c) base += (conveter(argv[2][i]) * (int)pow(16,c));

        base -= 0x10000000;
        base >>=2;
        
        for(int i=base;i<base+stoi(argv[3]);++i) cout << dec_to_hex(DATAM[i])<<"\n";
        return;
    }

    return;
}