#include <string.h>
#include "dfs.h"

int main(int argc, char * argv[]){
  if (argc==4) {
    int depart, arrivee;
  graph_t graph;
  graph = graph_read(argv[1],0, NULL);
  graph.initialise=0;
  depart=atoi(argv[2]);
  arrivee=atoi(argv[3]);
  if (DFS(depart, arrivee, &graph)!=0){
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
