#include <inttypes.h>
#include <stdlib.h>

#include "crc.h"


#define MAX_UINT32    0xFFFFFFFF

/* CITT CRC16 polynomial ^16 + ^12 + ^5 + 1 */
/* taken from https://github.com/contiki-ng/contiki-ng/blob/develop/os/lib/crc16.c*/
static uint16_t crc16_calculate(uint16_t acc, uint8_t b)
{
    acc ^= b;
    acc  = (acc >> 8) | (acc << 8);
    acc ^= (acc & 0xff00) << 4;
    acc ^= (acc >> 8) >> 4;
    acc ^= (acc & 0xff00) >> 5;
    return acc;
}

bool calculate_crc(FILE *firmware, metadata_t *metadata)
{
    if (firmware == NULL)
    {
        printf("Error: opened firmware file is NULL\n");
        return false;
    }



    fseek(firmware, 0, SEEK_END);           // move to the end of the file
    long int file_length = ftell(firmware); // read the byte offset
    rewind(firmware);                       // get back to the beginning of the file

    if (file_length > MAX_UINT32)
    {
        printf("File size is %lu. It is larger than the limit of metadata.size which is %" PRIu32 "", file_length, MAX_UINT32);
    }
    else
    {
        metadata->size = file_length;
    }

    uint8_t *buffer = (uint8_t *)malloc(file_length * sizeof(uint8_t));

    // TODO: experiment = reading entire buffer vs reading byte by byte vs reading chunk by chunk
    size_t result = fread(buffer, file_length, 1, firmware); // copy the entire file into the buffer
    if (result != 1)
    {
        printf("Error occured while copying the bin file into the temp buffer\n");
        return false;
    }

    fclose(firmware);                        // Close the file


    uint16_t crc16 = 0;
    for (long int idx = 0; idx < file_length; idx++)
    {
        crc16 = crc16_calculate(crc16, buffer[idx]);
    }

    free(buffer);
    metadata->crc = crc16;

    return true;
}
