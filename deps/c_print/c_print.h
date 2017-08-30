
//
// c_print.h
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#ifndef _C_PRINT_H_
#define _C_PRINT_H_


typedef enum 
{
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_GREY,
    COLOR_NORMAL,
    COLOR_MAX
}ColorCode;

int c_print(int, const char *, ...);

#endif
