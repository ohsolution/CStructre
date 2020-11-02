#include "header/definition.h"
#include "header/IO.h"
#include "header/parser.h"
#include "header/memory.h"
#include "header/CPU.h"

int checker(vector <string> sargv)
{
    if(!sargv.size()) return 0;

    if(sargv.size() == 1) return 1;

    if(sargv.size()==2) return sargv[2]=="reg";

    if(sargv.size()==)

    return false;
}



int main(int argc,char ** argv)
{
    vector <string> sargv;
    for(int i=2;i<argc;++i) sargv.push_back((string)argv[i]);

    int tp= checker(sargv);

    if(!tp) return 0;

    IO * stream = new IO(argv[1]);

    parser::save_ISM(stream->getbuf());
        
    CPU * cpu = new CPU(stoi((string)argv[2]));
    
    if(!(cpu->run())) cout << "unknown instruction\n";

    //stream->output(sargv,tp,cpu->getreg());
    
    return 0;
}
