#include "header/definition.h"
#include "header/disassembler.h"
#include "header/memory.h"


string disassembler::disassem(vector <int> vi)
{
    string ret = "";

    if(vi[0] == 0) // R-type
    {
        info cur = funhash[vi.back()];

        if(!cur.ty) goto WAEXIT;

        ret += cur.is+" ";

        string s= regname[vi[1]];
        string t= regname[vi[2]];
        string d = regname[vi[3]];
        string a= to_string(vi[4]);
        
        switch (cur.ty)
        {
            case ARITH:
                ret += d + ", " + s + ", " + t; 
                break;
            case DIVMUL:
                ret += s + ", " + t;
                break;
            case SHIFT:
                ret += d + ", " + t + ", " + a; 
            break;
            case SHIFTV:
                ret += d + ", " + t + ", " + s; 
            break;
            case JUMPR:
                ret += s;
            break;
            case JUMPLR:
                ret += d +", "+s;
            break;
            case MOVEFROM:
                ret += d;
            break;
            case MOVETO:
                ret += s;
            break;
            case SYSTEMCALL:
                ret.pop_back();
            break;
            default:
                break;
        }
    }   
    else if(vi[0] == 2 || vi[0] == 3)
    {
        ret += ophash[vi[0]].is+" ";
        ret += to_string(vi[1]);   
    }   
    else
    {
        info cur = ophash[vi[0]];

        if(!cur.ty) goto WAEXIT;

        ret += cur.is+" ";
        string s= regname[vi[1]];
        string t = regname[vi[2]];
        string IMM = to_string(vi[3]);

        switch (cur.ty)
        {
            case ARITHI:
                ret += t+", "+s+", "+IMM; 
                break;
            case LOADI:
                ret += t+", "+IMM;
                break;
            case BRANCH:
                ret+=s+", "+t+", "+IMM;
                break;
            case LOADSTORE:
                ret+=t+", "+IMM+"("+s+")";
                break;    
            default:
                break;
        }
    }

    return ret;

    WAEXIT:
    return "unknown instruction";
}