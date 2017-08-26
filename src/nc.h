
//
// nc.h
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//
#ifndef _NC_H_
#define _NC_H_

#include "list/list.h"

#define MAX_OPTIONS  12
#define MAX_NUMBERS  6

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
	struct list_head  toAll;
	struct list_head  toDec;
	struct list_head  toHex;
	struct list_head  toOct;
	struct list_head  toBin;
	struct list_head  toSig;
}options;

typedef struct {
   struct list_head  node;
   u8                oIndex;
   u8                bHasarg;
   char *            arg;
}option_info_t;


typedef struct{
    u8  numOfOpt;
    u8  index[MAX_OPTIONS];
    u8  numOfNum;
    u8  number[MAX_NUMBERS];
}control_info_t;

#endif
