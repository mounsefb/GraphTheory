#include "vertex.h"

void vertex_print(vertex_t *e){
  printf("nom du sommet : %s \n", e->nom);
  printf("coordonnees : (%lf , %lf) \n", e->x, e->y);
  printf("nom de ligne : %s \n", e->ligne);
  printf("cout actuel : %lf \n", e->pcc);
  printf("copain le plus proche actuel : %d \n", e->plusproche);
  printf("liste des arcs du sommet : \n");
  listedge_print(e->edges);
}
