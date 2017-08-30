
//
// number.h
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#ifndef _NUMBER_H_
#define _NUMBER_H_

#define TRUE    1
#define FALSE   0

typedef  int      BOOL;

BOOL is_bin(char *, int);
BOOL is_dec(char *);
BOOL is_hex(char *);
BOOL is_oct(char *);

int hex_to_dec(char *);
int bin_to_dec(char *);
int oct_to_dec(char *);
int dec_to_dec(char *);

char *dec_to_bin(int);

#endif 
