
//
// c_print.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "c_print.h"

static char *g_color[] = {
    "\x1b[31m", /*red*/  
    "\x1b[32m", /*green*/
    "\x1b[33m", /*yellow*/
    "\x1b[34m", /*blud*/
    "\x1b[35m", /*magenta*/
    "\x1b[36m", /*cyan*/
    "\x1b[0m" , /*normal*/
};

int c_print(int code,const char *fmt, ...)
{
    char *output;
    char *temp, *reset;
    int   size;
    va_list ap;
    
    if(code < 0 || code >= COLOR_MAX)
    {
        return -1;
    }

    va_start(ap, fmt);
    
    temp  = g_color[code];
    reset = g_color[COLOR_NORMAL];

    output = malloc(strlen(temp) + strlen(fmt) + strlen(reset)+1);
    if(!output)
    {
        return -1;
    }

    memset(output, 0, strlen(output));
    memcpy(output, temp, strlen(temp));
    memcpy(output+strlen(temp), fmt, strlen(fmt));
    memcpy(output+strlen(temp)+strlen(fmt), reset, strlen(reset)+1);

    size = vprintf(output,ap);
    if(output) free(output);
    va_end(ap);

    return size;
}
    

