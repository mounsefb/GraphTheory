#ifndef ELEMENTHASH_H
#define ELEMENTHASH_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef char* cle_t;
typedef int value_t;

typedef struct {
  cle_t cle;
  value_t value;
} element_t;

void element_print(element_t e);

#endif
