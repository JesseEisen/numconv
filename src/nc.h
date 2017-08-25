
//
// nc.h
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//
#ifndef _NC_H_
#define _NC_H_

typedef enum {
    NUMBER_TO_ALL = 1,
    NUMBER_TO_HEX,
    NUMBER_TO_OCT,
    NUMBER_TO_DEC,
    NUMBER_TO_SIG,
    NUMBER_TO_BIN,
    NUMBER_MAX
}convert_type;

typedef unsigned char  u8;

typedef struct {
	u8  toAll;
	u8  toDec;
	u8  toHex;
	u8  toOct;
	u8  toBin;
	u8  toSig;
}options;

#endif
