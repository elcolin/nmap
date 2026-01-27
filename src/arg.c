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
        fprintf(stderr, "%s: %s\n", msg, reason);
        exit(EXIT_FAILURE);
    }
}

const char *substr[] = {"--ports", "--file", "--ip", "--speedup", "--scan"};

int openFile(const char *fileName)
{
    int fd = open(fileName, O_RDONLY);
    triggerErrorNoFreeingIf(fd < 0, "openFile", strerror(errno));
    return fd;
}

void scanArguments(const int argc, const char **argv, Args *args)
{
    int destinationSetTo = COUNT_OPT;
    for (int argIdx = 0; argIdx < argc; argIdx++)
    {
        for (int optionIdx = 0; optionIdx < NUMBER_OF_OPTIONS; optionIdx++)
        {
            if (!strcmp(argv[argIdx], substr[optionIdx]))
            {
                triggerErrorNoFreeingIf(argIdx + 1 >= argc, "scanArguments", "Option requires values pos(");
                handleOption(optionIdx, argv[argIdx + 1], args);
                if (optionIdx == IP || optionIdx == NFILE)
                    destinationSetTo = optionIdx;
                break;
            }
        }
        // TODO add error if arg doesn't exist
    }
    triggerErrorNoFreeingIf(destinationSetTo == COUNT_OPT, "scanArguments", "No IP or file found.");
    if (destinationSetTo == NFILE)
        args->fdIp = openFile(args->fileArgument);
}

bool isArgumentValid(const char *arg)
{
    if (arg == NULL)
        return FALSE;
    size_t argLen = strlen(arg);
    if (argLen == 0)
        return FALSE;
    return TRUE;
}

bool isStrDigit(const char *str)
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

static __uint64_t getNumberFromStr(const char *str, const __uint64_t maxRange)
{
    triggerErrorNoFreeingIf(isStrDigit(str) == FALSE, "isStrDigit", "Argument isn't only digits.");
    __uint64_t number = atol(str);
    triggerErrorNoFreeingIf(number > maxRange, "getNumberFromStr", "Number is above max range.");
    triggerErrorNoFreeingIf(number <= 0, "getNumberFromStr", "Number is below or equal to 0.");
    return number;
}



void handleOption(const __uint8_t option, const char *str, Args *args)
{
    static bool destIsDefined = FALSE;

    triggerErrorNoFreeingIf(isArgumentValid(str) == FALSE, "isArgumentValid", "Argument format isn't correct.");
    switch (option)
    {
        case PORTS:
            args->ports = getNumberFromStr(str, MAX_PORT_NUMBER);
        break;
        case NFILE:
            triggerErrorNoFreeingIf(destIsDefined == TRUE, "handleOption", "Destination was already defined.");
            args->fileArgument = str;
            destIsDefined = TRUE;
        break;
        case IP:
            triggerErrorNoFreeingIf(destIsDefined == TRUE, "handleOption", "Destination was already defined.");
            triggerErrorNoFreeingIf(setDestinationAddress(&args->ip_addr, str) == FAILURE, "handleOption", "Incorrect destination.");
            destIsDefined = TRUE;
        break;
        case SPEEDUP:
            args->numberOfThreads = (__uint8_t) getNumberFromStr(str, MAX_NUMBER_OF_THREADS);
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
            triggerErrorNoFreeingIf(TRUE, "handleOPtion", "Scan option must have one of the following types : SYN, NULL, ACK, FIN, XMAS, UDP.");
        break;
        default:
        break;
    }
    
}

void printHelpAndExit()
{
    printf("Usage: ft_nmap [--help] [--ports [NUMBER/RANGED]] --ip IP_ADDRESS [--speedup [NUMBER]] [--scan [TYPE]]\
    ft_nmap [--help] [--ports [NUMBER/RANGED]] --file FILE [--speedup [NUMBER]] [--scan [TYPE]]");
    exit(EXIT_SUCCESS);
}