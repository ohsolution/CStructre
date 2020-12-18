#include "header/definition.h"
#include "header/pipe.h"
#include "header/memory.h"
#include "header/parser.h"

PIPE::PIPE(CPU * _cpu)
{
    vaild = false;
    cpu = _cpu;
}

void PIPE::Set_inst(INST _inst) 
{ 
    vaild = true;
    inst = _inst; 
}

void PIPE_ID::Set_instr(string _inst) 
{
    vaild = true;
    instr = _inst; 
}

PIPE_ID::PIPE_ID(CPU * _cpu):PIPE(_cpu) { Parser = new parser(); }
PIPE_IF::PIPE_IF(CPU * _cpu):PIPE(_cpu) { instr = ""; }
PIPE_EX::PIPE_EX(CPU * _cpu):PIPE(_cpu){;}
PIPE_MEM::PIPE_MEM(CPU * _cpu):PIPE(_cpu){;}
PIPE_WB::PIPE_WB(CPU * _cpu):PIPE(_cpu){;}

PIPE_ID::~PIPE_ID(){ delete Parser; }

string PIPE_IF::exec()
{   
    // fetch
    instr = ISM[(cpu->pc)>>2];
    cpu->lpc = cpu->pc;

    // pc handle
    if(instr.substr(0,6) == "000010") 
    {
        string tmp = instr.substr(6,26);
        reverse(tmp.begin(),tmp.end());
        int timm = 0;

        for(int i=0;i<26;++i) if(tmp[i] == '1') timm += (1<<i);
        
        cpu->pc = timm << 2;
    }
    else cpu->pc += 4;

    return instr;
}

INST PIPE_ID::exec()
{
    vector <int> vt = Parser->parsing(instr); // parsing    

    
    
    if(vt[0] == 2)
    {
        inst.tp = JTYPE;
        inst.imm = vt[1];
        instr[4] = '0';        
        inst.rsv = (Parser->parsing(instr))[1];
        instr[4] = '1';
    }
    else if(vt[0])
    {
        inst.tp = ITYPE;
        inst.code = vt[0];
        inst.rs = &(cpu->reg[vt[1]]);
        inst.rt = &(cpu->reg[vt[2]]);
        inst.rsv = *inst.rs;
        inst.rtv = *inst.rt;
        inst.imm = vt[3];
        inst.uimm = vt[3] + (1<<15) * !!( vt[3] &(1<<15));
    }
    else
    {
        
        inst.tp = RTYPE;
        inst.code = vt.back();
        inst.rs = &(cpu->reg[vt[1]]);
        inst.rt = &(cpu->reg[vt[2]]);
        inst.rd = &(cpu->reg[vt[3]]);
        inst.rsv = *inst.rs;
        inst.rtv = *inst.rt;
        inst.rdv = *inst.rd;
    }

    info x = vt[0] ? ophash[vt[0]] : funhash[vt.back()];

    cout << x.is <<" $"<<vt[2] << " $" << vt[1] << " " << inst.imm<<endl;

    cout << inst.rtv << " "<< inst.rsv << " "<<endl;

    cpu->checksum = (cpu->checksum << 1 | (int)((unsigned int)cpu->checksum >> 31)) ^ inst.rsv;

    return inst;
}

INST PIPE_EX::exec()
{
    if(inst.tp == ITYPE)
    {
        switch (inst.code)
        {   
        case 8: //addi SE
            inst.wval = inst.rsv + inst.imm;
            break;

        case 12: //andi ZE
            inst.wval = inst.rsv & inst.uimm;
            break;

        case 13: //ori ZE
            inst.wval = inst.rsv | inst.uimm;
            break;

        case 10: //slti SE
            inst.wval = (inst.rsv < inst.imm);
            break;

        case 15: //lui 
            inst.wval = inst.imm<<16;
            break;
        case 35: //lw
            inst.address = ((inst.rsv+inst.imm-0x10000000)>>2);
            break;

        case 43: //sw
            inst.wval = inst.rtv;
            inst.address = ((inst.rsv+inst.imm-0x10000000)>>2);//DATAM[((rsv+imm-0x10000000)>>2)] = rtv;
            break;    
        default:
            break;
        }        
    }    
    else if(inst.tp == RTYPE)
    {
        switch (inst.code)
        {   
        case 32: //add
            inst.wval = inst.rsv+inst.rtv;
            break;

        case 34: //sub
            inst.wval = inst.rsv-inst.rtv;
            break;

        case 36: //and
            inst.wval = inst.rsv&inst.rtv;
            break;

        case 37: //or
            inst.wval= inst.rsv | inst.rtv;
            break;

        case 42: //slt
            inst.wval = (inst.rsv < inst.rtv);
            break;               
        default:
            break;
        }
    }

    return inst;
}

INST PIPE_MEM::exec()
{
    if(inst.tp==ITYPE)
    {
        switch (inst.code)
        {   
        case 35: //lw
            inst.wval = DATAM[inst.address];
            break;

        case 43: //sw
            DATAM[inst.address] = inst.wval;
            break;    
        default:
            break;
        }       
    }

    return inst;
}

void PIPE_WB::exec()
{
    if(inst.tp == ITYPE)
    {
        switch (inst.code)
        {   
        case 8: //addi SE
        case 12: //andi ZE
        case 13: //ori ZE
        case 10: //slti SE
        case 15: //lui 
        case 35: //lw
            *inst.rt = inst.wval;
            break;
        default:
            break;
        }        
    }    
    else if(inst.tp == RTYPE)
    {
        switch (inst.code)
        {   
        case 32: //add
        case 34: //sub
        case 36: //and
        case 37: //or
        case 42: //slt
            *inst.rd = inst.wval;
            break;
        default:
            break;
        }
    }   
}