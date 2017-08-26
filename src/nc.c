
//
// nc.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commander/commander.h"
#include "c_print/c_print.h"
#include "list/list.h"
#include "strdup/strdup.h"
#include "nc.h"

options        g_option;
control_info_t g_ctrl = {0,{0},0,{0}};

#define IDX_ADD_ONE(x)  do{ g_ctrl.index[g_ctrl.numOfOpt++] = (x); }while(0)
#define IS_OPT_EXCEED   do{ if ( g_ctrl.numOfOpt >= MAX_OPTIONS ) \
                            { c_print(COLOR_RED, "Too many options\n"); exit(1); } \
                        }while(0)
#define RECORD_NUMBER_INDEX(x)  g_ctrl.number[g_ctrl.numOfNum++] = (x) 

void 
nt_init_optlist(void)
{
    INIT_LIST_HEAD(&(g_option.toAll));
    INIT_LIST_HEAD(&(g_option.toDec));
    INIT_LIST_HEAD(&(g_option.toHex));
    INIT_LIST_HEAD(&(g_option.toOct));
    INIT_LIST_HEAD(&(g_option.toBin));
    INIT_LIST_HEAD(&(g_option.toSig));
}

static void
nt_set_options( const char * arg, u8 type)
{
    option_info_t  info;
    memset(&info,0,sizeof(option_info_t));

    IS_OPT_EXCEED;
    IDX_ADD_ONE(type);
    
    info.oIndex = g_ctrl.numOfOpt - 1;
    if(arg)
    {
        info.bHasarg = 1;
        info.arg = strdup(arg);
        RECORD_NUMBER_INDEX(info.oIndex);
    }
    
    switch(type) {
        case NUMBER_TO_ALL:
            list_add(&(info.node),&(g_option.toAll));
            break;
        case NUMBER_TO_HEX:
            list_add(&(info.node),&(g_option.toHex));
            break;
        case NUMBER_TO_OCT:
            list_add(&(info.node),&(g_option.toOct));
            break;
        case NUMBER_TO_DEC:
            list_add(&(info.node),&(g_option.toDec));
            break;
        case NUMBER_TO_SIG:
            list_add(&(info.node),&(g_option.toSig));
            break;
        case NUMBER_TO_BIN:
            list_add(&(info.node),&(g_option.toBin));
            break;
        case NUMBER_MAX:
            // nerver run here
            break;
    }
}

static void 
nt_setopt_all(command_t *self)
{
    nt_set_options(self->arg, NUMBER_TO_ALL);
}

static void 
nt_setopt_bin(command_t *self)
{
    nt_set_options(self->arg, NUMBER_TO_BIN);
}

static void
nt_setopt_dec(command_t *self)
{
    nt_set_options(self->arg, NUMBER_TO_DEC);
}

static void
nt_setopt_oct(command_t *self)
{
    nt_set_options(self->arg, NUMBER_TO_OCT);
}

static void
nt_setopt_sign(command_t *self)
{
    nt_set_options(self->arg, NUMBER_TO_SIG);
}

static void
nt_setopt_hex(command_t *self)
{
    nt_set_options(self->arg, NUMBER_TO_HEX);
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
            "-b", "--bin [num]",
            "convert number to binary format",
            nt_setopt_bin);
    command_option(&cmd,
            "-d", "--dec [num]",
            "convert number to unsigned decimal format",
            nt_setopt_dec);
    command_option(&cmd,
            "-s", "--sign [num]",
            "convert number to signed decimal fromat",
            nt_setopt_sign);
    command_option(&cmd,
            "-h", "--hex [num]",
            "convert number to hex format",
            nt_setopt_hex);
    command_option(&cmd,
            "-o", "--oct [num]",
            "convert number to octal format",
            nt_setopt_oct);
    command_parse(&cmd, argc, argv);

#if 0
    int i;
    for(i = 0; i < g_ctrl.numOfOpt; i++) {
        printf("%d\n",g_ctrl.index[i]);
    }

    printf("numbers:\n");
    for(i = 0; i < g_ctrl.numOfNum; i++) {
        printf("%d\n",g_ctrl.number[i]);
    }
#endif 
    return 0;
}
