
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
#include "number/number.h"
#include "strdup/strdup.h"
#include "list/list.h"
#include "nc.h"

struct list_head   g_numList;;
control_info_t     g_ctrl = {0,{0}};
u8                 g_lastNum = 0;  /*last number index*/

#define IDX_ADD_ONE(x)  do{ g_ctrl.index[g_ctrl.numOfOpt] = x; }while(0)
#define IS_OPT_EXCEED   do{ if ( g_ctrl.numOfOpt >= MAX_OPTIONS ) \
                            { c_print(COLOR_RED, "Too many options\n"); exit(1); } \
                        }while(0)

#define UNUSED(x)    do{ if(x){} }while(0)

void 
nt_init_optlist(void)
{
    INIT_LIST_HEAD(&g_numList);
}

static number_type
nt_get_number_type(char *numStr)
{
    if(is_bin(numStr,1)) {
        return TYPE_BIN;
    } else if (is_dec(numStr)) {
        return TYPE_DEC;
    } else if (is_oct(numStr)) {
        return TYPE_OCT;
    } else if (is_hex(numStr)) {
        return TYPE_HEX;
    } else {
        return TYPE_MAX;
    }
    

    /* never run here*/
    return TYPE_MAX;
}

static void
nt_set_options(const char * arg, u8 type)
{
    number_info_t*  info;
    
    info = malloc(sizeof(number_info_t));
    if(!info)  return;

    IS_OPT_EXCEED;
    IDX_ADD_ONE(type);
    
    if(arg)
    {
        info->nIndex  = g_ctrl.numOfOpt;
        info->arg     = strdup(arg);
        info->numType = nt_get_number_type(info->arg); 
    }
    
    g_ctrl.numOfOpt++;
    list_add(&info->node, &g_numList);
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

#define A_TO_B(Src,src, dst) \
    case TYPE_##Src: res = src##_to_##dst(num); break

static void
convert_to_dec(char *num, number_type type) 
{
    int res;
    switch (type) {
        A_TO_B(BIN,bin,dec);
        A_TO_B(HEX,bin,dec);
        A_TO_B(OCT,bin,dec);
        A_TO_B(DEC,bin,dec);
        case TYPE_MAX:
            return;
    }

   UNUSED(res); 
}

static void
convert_to_hex(char *num, number_type type)
{

}

static void
convert_to_bin(char *num, number_type tyep)
{

}

static void
convert_to_oct(char *num, number_type type)
{

}

static void
convert_to_sig(char *num, number_type type)
{

}

static void
convert_to_all(char *num, number_type type)
{

}


#define  CONVERT_FUNC(X,x)  \
    case NUMBER_TO_##X: convert_to_##x(ni->arg, ni->numType); break

static void
nt_number_convert(number_info_t *ni)
{
     int i;

     for(i = g_lastNum; i <= ni->nIndex; i++)
     {
         switch(g_ctrl.index[i]) {
             CONVERT_FUNC(ALL,all);
             CONVERT_FUNC(DEC,dec);
             CONVERT_FUNC(HEX,hex);
             CONVERT_FUNC(BIN,bin);
             CONVERT_FUNC(OCT,oct);
             CONVERT_FUNC(SIG,sig);
             case NUMBER_MAX: 
                return;
         }
     }

     g_lastNum = ni->nIndex + 1;
}

int
main(int argc, char **argv)
{
    command_t     cmd;
    number_info_t *p;
    
    nt_init_optlist();

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

    list_for_each_entry(p, &g_numList,node) {
          nt_number_convert(p);     
    }
    
    return 0;
}
