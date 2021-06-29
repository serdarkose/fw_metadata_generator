#include <stdio.h>
#include <stdint.h>

#include "cli_validate.h"


bool validate_user_input(char **argv)
{
    //validate if all inputs are in place
    if (!argv[1])
    {
        printf("please enter .bin file as the first argument.\n");
        return false;
    }

    if (!argv[2])
    {
        printf("please enter version number of the firmware as the second argument.\n");
        return false;
    }

    if (!argv[3])
    {
        printf("please enter UUID as the third argument in 32-bit hex format.\n");
        return false;
    }

    for (int i = 0; i < 4; i++)
    {
        printf("arg %d : %s\n", i, argv[i]);
    }

    return true;
}
