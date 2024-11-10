#ifndef _DFS_H
#define _DFS_H
#include "divers.h"
#include "graph.h"
#include "listedge.h"
#define INFINI DBL_MAX

//Protoype des fonctions realisant les opérations essentielles du DFS

// Algorithme Depth Fisrt Search OU DFS
int DFS(int depart, int arrivee, graph_t* graphe);


#endif
