
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

struct list_head   g_numList;;
control_info_t     g_ctrl = {0,{0}};

#define IDX_ADD_ONE(x)  do{ g_ctrl.index[g_ctrl.numOfOpt++] = (x); }while(0)
#define IS_OPT_EXCEED   do{ if ( g_ctrl.numOfOpt >= MAX_OPTIONS ) \
                            { c_print(COLOR_RED, "Too many options\n"); exit(1); } \
                        }while(0)

void 
nt_init_optlist(void)
{
    INIT_LIST_HEAD(&g_numList);
}

static void
nt_set_options( const char * arg, u8 type)
{
    number_info_t  info;
    memset(&info,0,sizeof(number_info_t));

    IS_OPT_EXCEED;
    IDX_ADD_ONE(type);
    
    info.nIndex = g_ctrl.numOfOpt - 1;
    if(arg)
    {
        info.arg = strdup(arg);
        RECORD_NUMBER_INDEX(info.nIndex);
    }
    
    list_add(&(info->node), &g_numList);
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

#if 1
    int i;
    for(i = 0; i < g_ctrl.numOfOpt; i++) {
        printf("%d\n",g_ctrl.index[i]);
    }

    printf("numbers:\n");
    number_info_t *p;
    list_for_each_entry(&p->node, g_numList,node) {
        printf("%d: %s\n",p->nIndex, p->arg);
    }
#endif 
    return 0;
}
