#include "header/CPU.h"
#include "header/definition.h"
#include "header/memory.h"

CPU::CPU(int NumOfCycle)
{
    N = NumOfCycle;
    pc = checksum = 0;
    lpc = 0;
    reg.resize(32,0);
    
    pif = new PIPE_IF((CPU *)this);
    pid = new PIPE_ID((CPU *)this);
    pex = new PIPE_EX((CPU *)this);
    pmem = new PIPE_MEM((CPU *)this);
    pwb = new PIPE_WB((CPU *)this);
}

CPU::~CPU()
{
    reg.clear();
    delete pif;
    delete pid;
    delete pex;
    delete pmem;
    delete pwb;    
}

vector <int> CPU::getinfo(void) 
{
    vector <int> tmp(34);
    for(int i= 0 ; i<32 ; ++i) tmp[i] = reg[i]; 
    tmp[32] = lpc;
    tmp[33] = checksum;
    return tmp;
}

bool CPU::run()
{
        
    while(N--)
    {
        if(pwb->vaild) pwb->exec();        
        if(pmem->vaild) pwb->Set_inst(pmem->exec());
        if(pex->vaild) pmem->Set_inst(pex->exec());
        if(pid->vaild) pex->Set_inst(pid->exec());        
        pid->Set_instr(pif->exec());
    }

    cout << reg[4] << endl;

    return true;
}

/*

bool CPU::fetch()
{
    curinst = ISM[pc>>2];
    pc+=4;
    return curinst=="11111111111111111111111111111111" ? false : true;
}

*/




    /*
    while(N--&&fetch())
    {        
        if(curinst == "00000000000000000000000000000000") continue; //nop
        
        vector<int> vt = Parser->parsing(curinst);
        
        if(vt[0]==2) pc = vt[1]<<2;
        else if(vt[0])
        {
            int & rt = reg[vt[2]];
            int rtv = reg[vt[2]];
            int rsv = reg[vt[1]];
            int imm = vt[3];
            int uimm = vt[3] + (1<<15) * !!( vt[3] &(1<<15));
        
            switch (vt[0])
            {   
            case 8: //addi SE
                rt = rsv + imm;
                break;

            case 12: //andi ZE
                rt = rsv & uimm;
                break;

            case 13: //ori ZE
                rt = rsv | uimm;
                break;

            case 10: //slti SE
                rt = (rsv < imm);
                break;

            case 15: //lui 
                rt = imm<<16;
                break;
            case 35: //lw
                rt = DATAM[((rsv+imm-0x10000000)>>2)];
                break;

            case 43: //sw
                DATAM[((rsv+imm-0x10000000)>>2)] = rtv;
                break;    

            case 4: //beq
                if(rsv==rtv) pc += imm<<2;
                break;

            case 5: //bne
                if(rsv!=rtv) pc += imm<<2;
                break;            

            default:
                return 0;
                break;
            }
        }
        else
        {               
            int rsv = reg[vt[1]];
            int rtv = reg[vt[2]];
            int &rd = reg[vt[3]];

            switch (vt.back())
            {   
            case 32: //add
                rd = rsv+rtv;
                break;

            case 34: //sub
                rd = rsv-rtv;
                break;

            case 36: //and
                rd= rsv&rtv;
                break;

            case 37: //or
                rd= rsv | rtv;
                break;

            case 42: //slt
                rd = (rsv < rtv);
                break;   
                
            default:
                return 0;
                break;
            }
        }                
    }
    
    
    return N==-1;
    */