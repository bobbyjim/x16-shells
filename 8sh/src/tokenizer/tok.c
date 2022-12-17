#include <stdio.h>
#include <string.h>
#include <cx16.h>

#include "bank.h"
#include "scanner.h"

char *ram    = ((char *)(0xA000));

void main()
{
    char line[80];

    for(;;)
    {
        printf("%c ", '%');
        gets(line);
        setBank(SOURCE_BANK);
        strcpy(ram, line); 
        initTokenDebug();
        initScanner();
        scan();
    }
}
