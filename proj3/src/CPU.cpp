#include "header/CPU.h"
#include "header/definition.h"
#include "header/memory.h"

void ForwardingDetect(CPU * _cpu);
bool loadDetect(CPU *_cpu);
bool branchDetect(CPU *_cpu);
void branchForwarding(CPU *_cpu);

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

void CPU::run()
{        
    INST arr[4];
    arr[3].tp = DEFAULT;
    arr[3].rdv = arr[3].rtv = arr[3].rsv = 0;
    arr[3].rd = arr[3].rt = arr[3].rs = &reg[0];

    string ta = "";
    bool bubble = false;
    int C = 0;
    while(N--)
    {               
        if(arr[2].tp) pwb->Set_inst(arr[2]);
        if(arr[1].tp) pmem->Set_inst(arr[1]);
        if(arr[0].tp) pex->Set_inst(arr[0+bubble*3]);
        if(ta != "" && !bubble) pid->Set_instr(ta);

        ForwardingDetect(this);
                
        if(pwb->vaild) pwb->exec();                
        if(pmem->vaild) arr[2] = pmem->exec();
        if(pex->vaild) arr[1] = pex->exec();                
        if(pid->vaild) arr[0] = pid->exec();
        ta = pif->exec();        

        bubble = loadDetect(this);        
        
        branchForwarding(this);

        if(!bubble && branchDetect(this)) ta = "00000000000000000000000000000000";          
        
        //cout <<endl<< ++C << " : " << endl;
        //showpipe();
    }

    return;
}

void CPU::addBubble(PIPE * p1,PIPE * p2=NULL)
{
    INST t1;
    p1->inst= t1;
    pc-=4;
}

void CPU::showinfo(INST it)
{
    info x = it.tp==ITYPE ? ophash[it.code] : funhash[it.code];

    if(it.tp == ITYPE) cout<< x.is <<" $"<<((it.rt)-&reg[0]) << " $" << (it.rs-&reg[0]) << " " << it.imm<<" " << it.uimm<<endl;
    else cout << x.is << " $" << ((it.rd)-&reg[0]) << " $"<<((it.rs)-&reg[0]) << " $"<<((it.rt)-&reg[0]) << endl;
    cout << it.rdv << " "<< it.rsv << " "<< it.rtv<< endl;
}

void CPU::showpipe(void)
{
    cout << endl << endl;
    //if(pif) cout << "IF : "; showinfo(pif->inst); 
    if(pid) cout << "ID : "; showinfo(pid->inst); 
    if(pex) cout << "EX : "; showinfo(pex->inst); 
    if(pmem) cout << "MEM: ";showinfo(pmem->inst); 
    if(pwb) cout << "WB : ";showinfo(pwb->inst); 
    cout << endl << endl;

}


void ForwardingDetect(CPU * cpu)
{
    INST & wb = cpu->pwb->inst;
    INST & mem = cpu->pmem->inst;
    INST & ex = cpu->pex->inst;

    //cpu->showpipe();
    
    if(ex.tp == DEFAULT) return;
    
    int * memrd = (mem.tp == RTYPE ? mem.rd : mem.rt);
    int * exrs = ex.rs;
    int * exrt = (ex.tp == ITYPE ? NULL :ex.rt);
    if(ex.code == 43) exrt = ex.rt;
    
    if(mem.tp != DEFAULT)
    {
        if(mem.regWrite && (memrd != &cpu->reg[0])) //EX hazard
        {
            //cout << "D EX HAZARD DETECT !!!\n";
            //cout << "value  : "<< mem.wval<<endl;
            if(memrd == exrs) ex.rsv = mem.wval;
            if(memrd == exrt) ex.rtv = mem.wval;
        }
    }

    if(wb.tp == DEFAULT) return;

    int * wbrd = (wb.tp == RTYPE ? wb.rd : wb.rt);

    if(wb.regWrite && (wbrd != &cpu->reg[0])) // MEM hazard
    {
        //cout << "D MEM HAZARD DETECT !!!\n";
        //cout << "value  : "<< wb.wval<<endl;
        if(wbrd == exrs) ex.rsv = wb.wval;
        if(wbrd == exrt) ex.rtv = wb.wval;
    }

    return;     
}

void branchForwarding(CPU * cpu)
{    
    INST & mem = cpu->pmem->inst;
    INST & ex = cpu->pex->inst;
    INST & id = cpu->pid->inst;

    if(id.code !=4 && id.code!=5) return;

    int * exrd = (ex.tp == RTYPE ? ex.rd : ex.rt);
    int * idrs = id.rs;
    int * idrt = id.rt;
    
    if(ex.tp != DEFAULT)
    {   
        if(ex.regWrite && (exrd != &cpu->reg[0])) //EX hazard
        {
            //cout << "EX HAZARD DETECT !!!\n";
            if(exrd == idrs) id.rsv = ex.wval;
            if(exrd == idrt) id.rtv = ex.wval;
        }
    }

    if(mem.tp == DEFAULT) return;

    int * memrd = (mem.tp == RTYPE ? mem.rd : mem.rt);

    if(mem.regWrite && (memrd != &cpu->reg[0])) // MEM hazard
    {
        //cout << "MEM HAZARD DETECT !!!\n";
        
        if(memrd == idrs) id.rsv = mem.wval;
        if(memrd == idrt) id.rtv = mem.wval;
    }

    return;     
}

bool loadDetect(CPU *cpu)
{
    INST &ex = cpu->pex->inst;
    INST &id = cpu->pid->inst;

    /*
    cout << endl;
    cpu->showinfo(ex);
    cpu->showinfo(id);
    cout << endl;   
    */

    int * idrs = id.rs;
    int * idrt = (id.tp == RTYPE ? id.rt : NULL);
    if(id.code == 43 || id.code == 4 || id.code ==5) idrt = id.rt;

    //cout <<"check this : " << ex.rt <<" "<<idrs << endl;

    if(ex.code == 35 && (ex.rt == idrs || ex.rt == idrt)) 
    {
        //cout << "\n # # # addbubble # # #\n";
        cpu->pc -= 4;
        return true;
    }

    return false;    
}

bool branchDetect(CPU * cpu)
{
    INST tmp = cpu->pid->inst;

    if(tmp.code == 4) // beq
    {
        if(tmp.rsv == tmp.rtv)
        {
            cpu->pc -=4;
            cpu->pc += tmp.imm <<2;            
            return true;
        }
    }
    else if(tmp.code == 5) // bne
    {
        //cout << "tmp rsv : " << tmp.rsv << " rtv : " << tmp.rtv << endl;
        if(tmp.rsv != tmp.rtv)
        {
            cpu->pc -= 4;
            cpu->pc += tmp.imm <<2;            
            return true;
        }
    }

    return false;
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