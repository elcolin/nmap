#include "arg.h"

void findHelpArgument(const char **argv, const int argc)
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

void scanArguments(const int argc, const char **argv, Args *args)
{
    bool destinationIsSet = FALSE;
    for (int argIdx = 0; argIdx < argc; argIdx++)
    {
        for (int optionIdx = 0; optionIdx < NUMBER_OF_OPTIONS; optionIdx++)
        {
            if (!strcmp(argv[argIdx], substr[optionIdx]))
            {
                triggerErrorNoFreeingIf(argIdx + 1 >= argc, "scanArguments", "Option requires values pos(\n");
                handleOption(optionIdx, argv[argIdx + 1], args);
                if (optionIdx == IP || optionIdx == NFILE)
                    destinationIsSet = TRUE;

            }
        }
    }
    triggerErrorNoFreeingIf(destinationIsSet == FALSE, "scanArguments", "No IP or file found.\n");
}

bool argumentIsValid(const char *arg)
{
    if (arg == NULL)
        return FALSE;
    size_t argLen = strlen(arg);
    if (argLen == 0)
        return FALSE;
    return TRUE;
}

bool strIsDigit(const char *str)
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

const char *scanType[] = {"SYN", "NULL", "ACK", "FIN", "XMAS", "UDP"};


void handleOption(const __uint8_t option, const char *str, Args *args)
{
    triggerErrorNoFreeingIf(argumentIsValid(str) == FALSE, "argumentIsValid", "Argument format isn't correct.\n");
    switch (option)
    {
        case PORTS:
        //refactor SPEEDUP ?
            triggerErrorNoFreeingIf(strIsDigit(str) == FALSE, "strIsDigit", "Argument isn't only digits.\n");
            int portNumber = atoi(str);
            triggerErrorNoFreeingIf(portNumber > MAX_PORT_NUMBER, "handleOption", "Port number is above max range.\n");
            args->ports = (__uint16_t) portNumber;
        break;
        case NFILE:
        break;
        case IP:
            triggerErrorNoFreeingIf(setDestinationAddress(&args->ip_addr, str) == FAILURE, "handleOption", "Incorrect destination.\n");
        break;
        case SPEEDUP:
            triggerErrorNoFreeingIf(strIsDigit(str) == FALSE, "strIsDigit", "Argument isn't only digits.\n");
            int threadNumber = atoi(str);
            triggerErrorNoFreeingIf(threadNumber > MAX_NUMBER_OF_THREADS, "handleOption", "Thread number is above max range\n");
            args->numberOfThreads = (__uint8_t) threadNumber;
        break;
        case SCAN:
            for (int scanIdx = 0;  scanIdx < NUMBER_OF_SCAN_TYPES; scanIdx++)
            {
                if (!strcmp(scanType[scanIdx], str))
                {
                    args->scanType = scanIdx;
                    return;
                }
            }
            triggerErrorNoFreeingIf(TRUE, "handleOPtion", "Scan option must have one of the following types : SYN, NULL, ACK, FIN, XMAS, UDP.\n");
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