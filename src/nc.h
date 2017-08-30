
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

typedef enum {
    TYPE_DEC,
    TYPE_HEX,
    TYPE_BIN,
    TYPE_OCT,
    TYPE_MAX
}number_type;

typedef unsigned char  u8;

typedef struct {
   struct list_head  node;
   u8                nIndex;
   number_type       numType;
   char *            arg;
}number_info_t;


typedef struct{
    u8  numOfOpt;
    u8  index[MAX_OPTIONS];
}control_info_t;

typedef struct {
    struct list_head node;
    number_type      numType;
    union {
      int              res;
      char             *bin;
    };
}convert_res;

#endif
