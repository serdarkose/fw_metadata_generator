#ifndef METADATA_H
#define METADATA_H

#include <stdint.h>

typedef struct metadata_t
{
    uint32_t size;      // size of the firmware
    uint32_t uuid;      // unique FW ID (user defined)
    uint16_t crc;       // calculated CRC of the FW
    uint16_t version;   // version of the FW (user defined)
} metadata_t;


#endif
