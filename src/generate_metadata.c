#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#include "cli_validate.h"
#include "crc.h"
#include "metadata.h"


// ./generate_metadata firmware.bin 0x04 0xcafebabe
//                       bin file   ver   UUID
int main(int argc, char *argv[])
{
    if (!validate_user_input(argv))
    {
        printf("user input validation failed.\n");
        return -1;
    }

    metadata_t metadata;

    // open the file
    FILE *firmware_bin; // firmware.bin file that would be passed by the user

    firmware_bin = fopen(argv[1], "rb");
    if (firmware_bin == NULL) // could not open it
    {
        printf("Error: It could not open the file: %s \n", argv[1]);
        return -1;
    }

    // read the file and calculate teh CRC of the firmware
    if (!calculate_crc(firmware_bin, &metadata))
    {
        printf("Error occured during the CRC calculation.\n");
        return -1;
    }

    sscanf(argv[2], "%hxu", &(metadata.version));
    sscanf(argv[3], "%xu", &(metadata.uuid));

    uint8_t output_buffer[sizeof(metadata_t)];
    memset(output_buffer, 0, sizeof(output_buffer));
    memcpy(output_buffer, (uint8_t *)&metadata, sizeof(metadata_t));

    // export the metadata as a binary
    FILE *metadata_bin;
    metadata_bin = fopen("firmware-metadata.bin", "wb"); // create the bin file
    if (metadata_bin == NULL)
    {
        printf("Error occured while creating metadata_bin file\n");
        return -1;
    }

    // write the metadata into the file
    size_t result = fwrite(output_buffer, sizeof(output_buffer), 1, metadata_bin);
    if (result != 1)
    {
        printf("Error occured while writing into the metadata.bin file\n");
        return -1;
    }

    fclose(metadata_bin);

    printf("==== METADATA ===\n");
    printf("size: 0x%" PRIx32 "\n", metadata.size);
    printf("uuid: 0x%" PRIx32 "\n", metadata.uuid);
    printf("crc:  0x%" PRIx16 "\n", metadata.crc);
    printf("ver:  0x%" PRIu16 "\n", metadata.version);

    return 0;
}
