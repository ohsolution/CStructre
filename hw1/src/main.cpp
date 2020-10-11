#include "header/definition.h"
#include "header/IO.h"

string p_buf(unsigned char t)
{
    string ret;

    for(int i= 7; i >-1; --i)
    {
        int bit = 1<<i;

        if(t & bit) ret.push_back('1');
        else ret.push_back('0');
    }

    return ret;
}

int main(int argc,char ** argv)
{
    IO * stream = new IO(argv[1]);

    for(auto x : stream->buf) cout << p_buf(x) << endl;

    return 0;
}
