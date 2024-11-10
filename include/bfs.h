#ifndef _BFS_H
#define _BFS_H

#include "divers.h"
#include "fifoindice.h"
#include "graph.h"
#include "listedge.h"
//Protoype des fonctions realisant les opérations es sentielles de PCC en largueur

// retourne 1 si PCC existant, 0 sinon
int ParcoursEnLargeur(int depart, int arrivee, graph_t graphe);

#endif
