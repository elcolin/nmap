#include "arg.h"

void findHelpArgument(char **argv, int argc)
{
    for (int i = 0; i < argc; i++)
    {
        if(!strcmp(argv[i], "--help"))
            printHelpAndExit();
    }
}

void triggerErrorNoFreeingIf(const bool condition, const char *msg, const char *reason)
{
    if (condition)
    {
        fprintf(stderr, "%s: %s", msg, reason);
        exit(EXIT_FAILURE);
    }
}

const char *substr[] = {"--ports", "--file", "--ip", "--speedup", "--scan"};

void scanArguments(int argc, char **argv, Args *args)
{
    const char *funcName = "scanArguments";
    for (int argIdx = 0; argIdx < argc; argIdx++)
    {
        for (int optionIdx = 0; optionIdx < NUMBER_OF_OPTIONS; optionIdx++)
        {
            if (!strcmp(argv[argIdx], substr[optionIdx]))
            {
                triggerErrorNoFreeingIf(argIdx + 1 >= argc, funcName, "Option requires values pos(\n");
                handleOption(optionIdx, argv[argIdx + 1], args);
            }
        }
    }
}

bool argumentIsValid(char *arg)
{
    if (arg == NULL)
        return FALSE;
    size_t argLen = strlen(arg);
    if (argLen == 0)
        return FALSE;
    return TRUE;
}

bool strIsDigit(char *str)
{
    const size_t strLength = strlen(str);
    if (!strLength)
        return FALSE;
    for (size_t strIdx = 0; strIdx < strLength; strIdx++)  
    {
        if (isdigit(str[strIdx]) == FALSE)
            return FALSE;
    }
    return TRUE;
}

void handleOption(__uint8_t option, char *str, Args *args)
{
    triggerErrorNoFreeingIf(argumentIsValid(str) == FALSE, "argumentIsValid", "Argument format isn't correct.\n");
    switch (option)
    {
        case PORTS:
            triggerErrorNoFreeingIf(strIsDigit(str) == FALSE, "strIsDigit", "Argument isn't only digits.\n");
            int portNumber = atoi(str);
            triggerErrorNoFreeingIf(portNumber > MAX_PORT_NUMBER, "handleOption", "Port number is above max range.\n");
            args->ports = (__uint16_t) portNumber;
        break;
        case NFILE:
        break;
        case IP:
        break;
        case SPEEDUP:
            triggerErrorNoFreeingIf(strIsDigit(str) == FALSE, "strIsDigit", "Argument isn't only digits.\n");
            int threadNumber = atoi(str);
            triggerErrorNoFreeingIf(threadNumber > MAX_NUMBER_OF_THREADS, "handleOption", "Thread number is above max range\n");
            args->numberOfThreads = (__uint8_t) threadNumber;
        break;
        case SCAN:
        break;
        default:
        break;
    }
    
}

void printHelpAndExit()
{
    printf("Usage: ft_nmap [--help] [--ports [NUMBER/RANGED]] --ip IP_ADDRESS [--speedup [NUMBER]] [--scan [TYPE]]\n\
    ft_nmap [--help] [--ports [NUMBER/RANGED]] --file FILE [--speedup [NUMBER]] [--scan [TYPE]]");
    exit(EXIT_SUCCESS);
}