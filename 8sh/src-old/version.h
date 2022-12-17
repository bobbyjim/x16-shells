#ifndef _version_h_
#define _version_h_

#include <stdint.h>
#include "common.h"

#define VERSION_ADDR    0xff80

uint8_t getVersion();
uint8_t isProto();
uint8_t determineBankCount();

#endif
