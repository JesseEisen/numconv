
//
// number.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "number.h"


BOOL 
is_bin(char *str, int bprefix) 
{
    if(!str)  return FALSE;
    
    char c ;
    int len; 

    while(*str == ' ') {
        str++;
        continue;
    }

    if(bprefix) {
        
        if(str[0] != '0') {
            return FALSE;
        }
        
        if(str[1] != 'b') {
            return FALSE;
        }
       
        // remove prefix
        len = strlen(str) - 2;
        // "0b"
        if(len <= 0) return FALSE;

        memcpy(str,str+2,len); 
        *(str+len) = '\0';
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
    
    //distingush from octal
    if(*str++ == '0') return FALSE;

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
    int res;
    char *endptr;

    res = strtol(str,&endptr,16);
    if(*endptr == '\0') {
        return res;
    }
    
    return -1;
}

int 
oct_to_dec(char *str)
{
    int res;
    char *endptr;
    
    res = strtol(str, &endptr, 8);
    if(*endptr == '\0') {
        return res;
    }

    return -1;
}

int
dec_to_dec(char *str)
{
    return atoi(str);
}

char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

char *
dec_to_bin(int n)
{
    char * res = malloc(32);
    
    itoa(n,res,2);

    return res;
}

