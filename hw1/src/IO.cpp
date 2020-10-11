#include "header/IO.h"
#include "header/definition.h"

IO::IO(char * arg)
{
    ifstream input(arg,ios::binary);
    buf = vector <unsigned char>(istreambuf_iterator<char>(input),{});
}

IO::~IO(void)
{
    buf.clear();
}