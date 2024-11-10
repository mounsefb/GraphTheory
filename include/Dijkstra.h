#ifndef _Dijkstra_H
#define _Dijkstra_H

#include "divers.h"
#include "heap.h"
#include "listedge.h"
#include "graph.h"
#define INFINI DBL_MAX

// retourne 1 si PCC existant, 0 sinon
int Dijkstra_like(int depart, int arrivee, graph_t graphe);

#endif
