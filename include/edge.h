#ifndef _EDGES_H
#define  _EDGES_H
#include <stdio.h>
#include <stdlib.h>

// un arc
typedef
  struct { int depart, arrivee; double cout;  } edge_t;

// Affiche un arc
void edge_print (edge_t* e);
// Teste si 2 arc sont identique
int edge_equal(edge_t* e1, edge_t* e2);

#endif
