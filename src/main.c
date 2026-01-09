#include "ft_nmap.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
        printHelpAndExit();
    ++argv;
    findHelpArgument((const char **)argv, --argc);
    Args inputArgs = {};
    scanArguments(argc, (const char **)argv, &inputArgs);
    return 0;
}