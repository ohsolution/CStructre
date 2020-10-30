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

vector <unsigned char> * IO::getbuf(void)
{
    return &buf;
}

void IO::print(vector<string> * output)
{
    for(auto x : *output) cout << x << "\n";
    return;
}
