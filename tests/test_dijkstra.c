#include <string.h>
#include "Dijkstra.h"

int main(int argc, char * argv[]){
  if (argc==4) {
    int depart, arrivee;
  graph_t graph;
  graph = graph_read(argv[1],0, NULL);
  depart=atoi(argv[2]);
  arrivee=atoi(argv[3]);
  if (Dijkstra_like(depart, arrivee, graph)==1){
    printf("Valeur du PCC de %s entre %s et %s : %lf \n", argv[1], graph.data[depart].nom, graph.data[arrivee].nom, graph.data[arrivee].pcc);
  }
  else{
    printf("aucun chemin ne relie ces sommets \n");
  }
  graph_delete(graph);
  }
  else{
    printf("entree le nom d'un fichier \n");
  }
  return EXIT_SUCCESS;
}
