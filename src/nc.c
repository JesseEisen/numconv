
//
// nc.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commander/commander.h"

static void 
nt_setopt_all(command_t *self)
{
    
}

int
main(int argc, char **argv)
{
    command_t cmd;
    command_init(&cmd,argv[0],"0.0.1");
    command_option(&cmd,
            "-a","--all <num>",
            "convert number to all formats",
            nt_setopt_all);
    command_option(&cmd,
            "-b", "--bin <num>",
            "convert number to binary format",
            nt_setopt_bin);
    command_option(&cmd,
            "-d", "--dec <num>",
            "convert number to unsigned decimal format",
            nt_setopt_dec);
    command_option(&cmd,
            "-s", "--sign <num>",
            "convert number to signed decimal fromat",
            nt_setopt_sign);
    command_option(&cmd,
            "-h", "--hex <num>",
            "convert number to hex format",
            nt_setopt_hex);
    command_option(&cmd,
            "-o", "--oct <num>",
            "convert number to octal format,
            nt_setopt_oct);
    command_parse(&cmd, argc, argv);


}
