
//
// number.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "number.h"


BOOL 
is_bin(char *str, int bprefix) 
{
    if(!str)  return FALSE;
    
    char c ;

    while(*str == ' ') {
        str++;
        continue;
    }

    if(bprefix) {
        if(*str++ != '0' && *str != 'b') {
            return FALSE;
        }

        // '0b'
        if(*++str == '\0') return FALSE;
    } 

    while((c = *str++)) {
        if((c != '1') && (c != '0')) {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL
is_dec(char *str) 
{
    if(!str) return FALSE;
    
    char c; 

    while(*str == ' ')  {
        str++;
        continue;
    }

    //test sign characters
    if(*str == '+' || *str == '-') str++;
    
    while((c = *str++)) {
        if(!isdigit(c)) {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL
is_hex(char *str)
{
    if(!str) return FALSE;
    
    char c;

    while(*str == ' ') {
        str++;
        continue;
    }
    
    if((*str++ != '0')) 
        return FALSE;

    if(*str != 'x' &&  *str != 'X')
        return FALSE;
    
    str++;
    while((c = *str++)) {
        if(!isxdigit(c)) {
            return FALSE;
        }
    }

    return TRUE;

}

BOOL
is_oct(char *str)
{
    if(!str)  return FALSE;

    char c;

    while(*str == ' ') {
        str++;
        continue;
    }

    if(*str++ != '0') {
        return FALSE;
    }

    while((c=*str++)) {
        if( c < '0' || c > '7')
            return FALSE;
    }

    return TRUE;
}


int 
bin_to_dec(char *str)
{
    int   res;
    char *endptr;

    res = strtol(str,&endptr,2);
    if(*endptr == '\0') {
        return res;
    } 

    return -1;
}

int
hex_to_dec(char *str)
{

}

int 
oct_to_dec(char *str)
{

}

int
dec_to_dec(char *str)
{

}
