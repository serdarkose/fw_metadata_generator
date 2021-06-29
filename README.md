# fw_metadata_generator
CLI to generate a metadata from a firmware (.bin)

This CLI uses the below metadata format
- `size`: size of the firmware image.
- `uuid`: unique firmware ID. `UUID` would be used to identify the firmware.
- `crc` : calculating CRC of the firmware. `CRC` could be used to verify a firmware
- `version`: firmware version. 

# Installation
1. Download the project:

`$ git clone git@github.com:serdarkose/fw_metadata_generator.git`

2. Compile it:

`$ make`

`generate_metadata` binary would be generated.


# Usage
When `generate_metadata` binary is generated, then you can use it as

`$ ./generate_metadata <firmware.bin> <version> <uuid>`

- `<firmware.bin>` would specify the binary file that the CLI should work on.
- `<version>` would specify the version number of the firmware. This argument needs to be in hex format.
- `<uuid>` would specify the unique ID of the firmware. This argument needs to be in hex format.

Example: 

`$ ./generate_metadata firmware.bin 0x01 0xcafebabe`

# License

[Apache 2.0](LICENSE)
