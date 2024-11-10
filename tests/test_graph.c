#include "graph.h"

int main(int argc, char * argv[]){
  if (argc==2) {
  graph_t graph;
  graph = graph_read(argv[1],0, NULL);
  printf("lecture OK \n");
  graph_print(graph);
  graph_delete(graph);
  }
  else{
    printf("entree le nom d'un fichier \n");
  }
  return EXIT_SUCCESS;
}
