#include "ft_nmap.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
        printHelpAndExit();
    findHelpArgument(++argv, --argc);
    Args inputArgs = {};
    scanArguments(argc, argv, &inputArgs);
}