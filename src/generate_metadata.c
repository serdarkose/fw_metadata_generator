#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cli_validate.h"

#define DEBUG    1

#if DEBUG
#define PRINTF(...)    printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif


typedef struct metadata_t
{
    uint32_t size;      //size of the firmware
    uint32_t uuid;      // unique FW ID (user defined)
    uint16_t crc;       // calculated CRC of the FW
    uint16_t version;   // version of the FW (user defined)
} metadata_t;



// ./generate_metadata firmware.bin 0x04 0xcafebabe
//                       bin file   ver   UUID
int main(int argc, char *argv[])
{
    if (validate_user_input(argv))
    {
        return -1;
    }


    return 0;
}
