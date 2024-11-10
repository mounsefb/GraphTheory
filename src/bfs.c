#include "bfs.h"

int ParcoursEnLargeur(int depart, int arrivee, graph_t graph){
  fifoint_t f;
  int indiceU;
  double DistTemp;
  f=fifoint_new(); // 1 appel de fonction ( 1 opération ) + 1 opération
  int i;
  for(i=0; i<graph.size_vertex; i++){ //Parcours de tous les sommets du graph à l'aide d'une boucle for
   graph.data[i].pcc=LONG_MAX; //si l'indice du sommet que l'on teste correspond à l'indice du sommet de départ, alors son coût est initialisé à zéro, Sinon, son coût est initialisé à une valeur représentant l'infini
  }
  graph.data[depart].pcc=0;
  f=fifoint_enqueue(depart, f); // 1 appel de fonction ( 7 opérations )
  listedge_t arc;
  int arr;
  while( ! (fifoint_is_empty(f))) { // dans le pire des cas : n itérations
    indiceU=fifoint_dequeue(&f); // 5 opérations
    graph.data[indiceU].visited=0; // 1 opération
    if(graph.data[indiceU].pcc<=graph.data[arrivee].pcc){ // 1 opération
      for(arc = graph.data[indiceU].edges; arc != NULL; arc = arc->next){
        arr=arc->val.arrivee;
        DistTemp = graph.data[indiceU].pcc + arc->val.cout;
        if(DistTemp < graph.data[arr].pcc){ // 1 opération
          graph.data[arr].pcc = DistTemp; // 1 opération
          graph.data[arr].plusproche=indiceU; // 1 opé
          if(! graph.data[arr].visited) { // 1 opération
            f=fifoint_enqueue(arr, f); // 7 opérations
            graph.data[arr].visited=1; // 1 opération
          }
        }
      }
    }
  }
  if(graph.data[arrivee].pcc != LONG_MAX){ // 1 opération
    return 1;
  }
  return 0;
}
