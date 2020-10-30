#include "header/definition.h"

unordered_map<int,info> ophash
({
    {8,{"addi",1}},{9,{"addiu",1}},{12,{"andi",1}},{13,{"ori",1}},{14,{"xori",1}},{9,{"sltiu",1}},{10,{"slti",1}}, // ArithlogI
    {15,{"lui",2}},//LoadI
    {4,{"beq",3}},{5,{"bne",3}},//Branch
    {32,{"lb",4}},{36,{"lbu",4}},{33,{"lh",4}},{37,{"lhu",4}},{35,{"lw",4}},{40,{"sb",4}},{41,{"sh",4}},{43,{"sw",4}},//LoadStore
    {2,{"j",5}},{3,{"jal",5}} // Jump
});
unordered_map<int,info> funhash
({
    {32,{"add",1}},{33,{"addu",1}},{36,{"and",1}},{39,{"nor",1}},{37,{"or",1}},{34,{"sub",1}},{35,{"subu",1}},
    {38,{"xor",1}},{42,{"slt",1}},{41,{"sltu",1}}, // Arithlog
    {26,{"div",2}},{27,{"divu",2}},{24,{"mult",2}},{25,{"multu",2}}, //DivMult
    {0,{"sll",3}},{3,{"sra",3}},{2,{"srl",3}},//Shift
    {4,{"sllv",4}},{7,{"srav",4}},{6,{"srlv",4}},//ShiftV
    {8,{"jr",5}},//JumpR
    {16,{"mfhi",6}},{18,{"mflo",6}},//MoveFrom
    {17,{"mthi",7}},{19,{"mtlo",7}},//MoveTo
    {12,{"syscall",8}}, // systemcall
    {9,{"jalr",9}} // JumpLR
});

string regname[32]={"$0","$1","$2","$3","$4","$5","$6","$7","$8","$9","$10","$11","$12",
"$13","$14","$15","$16","$17","$18","$19","$20","$21","$22","$23","$24","$25","$26","$27",
"$28","$29","$30","$31"};