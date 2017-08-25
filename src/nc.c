
//
// nc.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commander/commander.h"
#include "nc.h"

options option = {
    .toAll = 0,
    .toDec = 0,
    .toHex = 0,
    .toOct = 0,
    .toBin = 0,
    .toSig = 0,
};

static void 
nt_setopt_all(command_t *self)
{
    option.toAll = NUMBER_TO_ALL;
}

static void 
nt_setopt_bin(command_t *self)
{
    option.toBin = NUMBER_TO_BIN;
}

static void
nt_setopt_dec(command_t *self)
{
    option.toDec = NUMBER_TO_DEC;
}

static void
nt_setopt_oct(command_t *self)
{
    option.toOct = NUMBER_TO_OCT;
}

static void
nt_setopt_sign(command_t *self)
{
    option.toSig = NUMBER_TO_SIG;

}

static void
nt_setopt_hex(command_t *self)
{
    option.toHex = NUMBER_TO_HEX;
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
            "convert number to octal format",
            nt_setopt_oct);
    command_parse(&cmd, argc, argv);

    printf("%d %d %d %d %d %d\n",
            option.toAll,
            option.toBin,
            option.toDec,
            option.toHex,
            option.toOct,
            option.toSig);
    return 0;
}
