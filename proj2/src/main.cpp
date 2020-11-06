#include "header/definition.h"
#include "header/IO.h"
#include "header/parser.h"
#include "header/memory.h"
#include "header/CPU.h"

int tp;

bool checker(vector <string> sargv)
{
    if(!sargv.size()) return true;

    if(sargv.size() == 1) tp = NOPRINT;
    
    for(auto x : sargv[0])
    {
        if(x <= '9' && x>='0') continue;
        return false;
    }

    if(sargv.size()==2) tp = REGPRINT * (sargv[1]=="reg");

    if(sargv.size()==4)
    {
        tp = MEMPRINT * (sargv[1]=="mem");
        bool tk = sargv[2].size()==10 && sargv[2][0]=='0' && sargv[2][1]=='x';
        if(tk) for(int i=2;i<sargv[2].size();++i) tk &= (sargv[2][i]>='0' || sargv[2][i]<='9');

        for(auto x : sargv[3])
        {
            if(x <= '9' && x>='0') continue;
            return tp=false;
        }

        tp *= tk;        
    }

    return !!tp;
}



int main(int argc,char ** argv)
{
    vector <string> sargv;
    for(int i=2;i<argc;++i) sargv.push_back((string)argv[i]);

    if(!checker(sargv)) return 0;

    IO * stream = new IO(argv[1]);

    parser::save_ISM(stream->getbuf());
        
    CPU * cpu = new CPU(stoi((string)argv[2]));
    
    if(!(cpu->run())) cout << "unknown instruction\n";

    stream->output(sargv,tp,cpu->getinfo());
    
    return 0;
}
