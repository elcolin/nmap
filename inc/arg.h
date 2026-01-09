#ifndef ARG_H
#define ARG_H


#include <stdio.h> // printf, exit
#include <stdlib.h> //EXIT_X
#include <string.h> //strcmp
#include <ctype.h> // isdigit
#include "utils.h"

#define DEFAULT_NUMBER_OF_THREADS 0
#define MAX_NUMBER_OF_THREADS 250
#define MAX_PORT_NUMBER 65535

#define NUMBER_OF_SCAN_TYPES 6

typedef enum {
    SYN, 
    NONE,// NULL ?
    ACK, 
    FIN, 
    XMAS, 
    UDP,
    ALL
    
} ScanType;

typedef struct {
    bool        selectedOptions[6];

    // bool        specificNumberOfPorts;
    __uint16_t  ports;
    // bool        usingIp;
    char        *ipArgument;
    // bool        usingFile;
    char        *fileArgument;
    // bool        specificNumberOfThreads;
    __uint8_t   numberOfThreads;
    // bool        specificScanType;
    __uint8_t   scanType;
    
} Args;

#define NUMBER_OF_OPTIONS 5

typedef enum {
    PORTS,
    NFILE,
    IP,
    SPEEDUP,
    SCAN
} Options;

void findHelpArgument(const char **argv, const int argc);
void printHelpAndExit();
void handleOption(const __uint8_t option, const char *str, Args *args);
void scanArguments(const int argc, const char **argv, Args *args);

#endif