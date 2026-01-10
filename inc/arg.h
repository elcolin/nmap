#ifndef ARG_H
#define ARG_H


#include <stdio.h> // printf, exit
#include <stdlib.h> //EXIT_X
#include <string.h> //strcmp
#include <ctype.h> // isdigit
#include "utils.h"
#include "addr.h"

#define DEFAULT_NUMBER_OF_THREADS 0
#define MAX_NUMBER_OF_THREADS 250
#define MAX_PORT_NUMBER 65535

#define NUMBER_OF_SCAN_TYPES 6
#define NUMBER_OF_OPTIONS 5

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
    __uint16_t          ports;
    char                *ipArgument;
    struct sockaddr_in  ip_addr;
    char                *fileArgument;
    int                 fdIp;
    __uint8_t           numberOfThreads;
    __uint8_t           scanType;
    
} Args;


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