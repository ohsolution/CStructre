#include "header/definition.h"
#include "header/IO.h"
#include "header/parser.h"

int main(int argc,char ** argv)
{
    IO * stream = new IO(argv[1]);

    parser * output = new parser(stream->getbuf());

    stream->print(output->getret());

    return 0;
}
