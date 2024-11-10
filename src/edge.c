#include "edge.h"

void edge_print (edge_t * e){ //Affiche un arc
  printf("depart = %d, arrivee = %d, cout = %lf", e->depart, e->arrivee, e->cout);
}

int edge_equal(edge_t* e1, edge_t* e2){ //Compare deux arcs pour vérifier leur égalité
  if (e1->depart==e2->depart && e1->arrivee==e2->arrivee && e1->cout==e2->cout ){
    return 1;
  }
  return 0;
}
