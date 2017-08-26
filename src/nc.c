
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

options        g_option;
control_info_t g_ctrl = {0,{0},0,{0}};

#define IDX_ADD_ONE(x)  do{ g_ctrl.index[g_ctrl.numOfOpt++] = (x); }while(0)
#define IS_OPT_EXCEED   do{ if ( g_ctrl.numOfOpt >= MAX_OPTIONS ) \
                            { c_print(COLOR_RED, "Too many options\n"); eixt(1); } \
                        }while(0)

void nt_init_optlist(void)
{
    INIT_LIST_HEAD(&(g_option.toAll));
    INIT_LIST_HEAD(&(g_option.toDec));
    INIT_LIST_HEAD(&(g_option.toHex));
    INIT_LIST_HEAD(&(g_option.toOct));
    INIT_LIST_HEAD(&(g_option.toBin));
    INIT_LIST_HEAD(&(g_option.toSig));
}

static void 
nt_setopt_all(command_t *self)
{
    option_info_t  all;
    memset(&all,0,sizeof(option_info_t));

    IS_OPT_EXCEED;
    IDX_ADD_ONE(NUMBER_TO_ALL);
    
    all.oIndex = g_ctrl.numOfOpt - 1;
    if(self->arg)
    {
        all.bHasArg = 1;
        all.arg = self->arg;
    }
    
    list_add(&(all.node), &(g_option.toAll));
}

static void 
nt_setopt_bin(command_t *self)
{
    option_info_t  bin;
    memset(&bin,0,sizeof(option_info_t));

    IS_OPT_EXCEED;
    IDX_ADD_ONE(NUMBER_TO_BIN);
    
    bin.oIndex = g_ctrl.numOfOpt - 1;
    if(self->arg)
    {
        bin.bHasArg = 1;
        bin.arg = self->arg;
    }
    
    list_add(&(bin.node), &(g_option.toBin));
}

static void
nt_setopt_dec(command_t *self)
{
    option_info_t  dec;
    memset(&dec,0,sizeof(option_info_t));

    IS_OPT_EXCEED;
    IDX_ADD_ONE(NUMBER_TO_DEC);
    
    dec.oIndex = g_ctrl.numOfOpt - 1;
    if(self->arg)
    {
        dec.bHasArg = 1;
        dec.arg = self->arg;
    }
    
    list_add(&(dec.node), &(g_option.toDec));
}

static void
nt_setopt_oct(command_t *self)
{
    option_info_t  oct;
    memset(&oct,0,sizeof(option_info_t));

    IS_OPT_EXCEED;
    IDX_ADD_ONE(NUMBER_TO_OCT);
    
    oct.oIndex = g_ctrl.numOfOpt - 1;
    if(self->arg)
    {
        oct.bHasArg = 1;
        oct.arg = self->arg;
    }
    
    list_add(&(oct.node), &(g_option.toOct));
}

static void
nt_setopt_sign(command_t *self)
{
    option_info_t  sig;
    memset(&sig,0,sizeof(option_info_t));

    IS_OPT_EXCEED;
    IDX_ADD_ONE(NUMBER_TO_SIG);
    
    sig.oIndex = g_ctrl.numOfOpt - 1;
    if(self->arg)
    {
        sig.bHasArg = 1;
        sig.arg = self->arg;
    }
    
    list_add(&(sig.node), &(g_option.toSig));

}

static void
nt_setopt_hex(command_t *self)
{
    option_info_t  hex;
    memset(&hex,0,sizeof(option_info_t));

    IS_OPT_EXCEED;
    IDX_ADD_ONE(NUMBER_TO_HEX);
    
    hex.oIndex = g_ctrl.numOfOpt - 1;
    if(self->arg)
    {
        hex.bHasArg = 1;
        hex.arg = self->arg;
    }
    
    list_add(&(hex.node), &(g_option.toHex));
}


int
main(int argc, char **argv)
{
    nt_init_optlist();
   
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

    return 0;
}
