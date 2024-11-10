#include "Dijkstra.h"
#include "time.h"

int Dijkstra_like(int depart, int arrivee, graph_t graph) {
  clock_t cl;
  heap_t t;
  int indiceU, intermed, i;
  double DistTemp;
  int tmp;
  t.number=0;
  t.max_size=graph.size_vertex;
  t.data=calloc(graph.size_vertex, sizeof(int)); // O(m) pire des cas/ O(mlog(m)) meilleur des cas
  if(t.data==NULL) exit(EXIT_FAILURE);
  for(i=0; i<graph.size_vertex; i++){ //Parcours de tous les sommets du graph à l'aide d'une boucle for
   graph.data[i].pcc=LONG_MAX; //si l'indice du sommet que l'on teste correspond à l'indice du sommet de départ, alors son coût est initialisé à zéro, Sinon, son coût est initialisé à une valeur représentant l'infini
  }
  graph.data[depart].pcc=0;
  heap_add_graph(depart, &t, graph); // O(n) opés dans le pire des cas / O(1) opés dans le meilleur
  vertex_t * data=graph.data;
  while (!heap_is_empty(t)) { // dans le pire des cas : n itérations / dans le meilleur des cas : 1 itération
    indiceU = t.data[0]; // 2 opés
    if(heap_delete_max_graph(&t, graph)){ // O(n) dans le pire des cas / O(1) sinon
      data[indiceU].visited = 0; // 1 opé
      if (indiceU == arrivee) {
        free(t.data); // 1 opé
        return 1;
      }
      int arr;
      listedge_t arc;
      if(data[indiceU].pcc<data[arrivee].pcc){
        for (arc = data[indiceU].edges; arc != NULL; arc = arc->next) { // m opérations
          arr=arc->val.arrivee;
          DistTemp = data[indiceU].pcc + arc->val.cout;
          if (DistTemp < data[arr].pcc) { // 1 opé
            data[arr].pcc = DistTemp; // 1 opé
            data[arr].plusproche=indiceU; // 1 opé
            if (!data[arr].visited) { // 1 opé
              data[arr].indiceTas = heap_add_graph(arr, &t, graph); // O(n) dans le pire des cas / O(1) sinon
              data[arr].visited = 1; // 1 opé
            }
            else {
              intermed=data[arr].indiceTas;
              t=heap_resort(intermed, t, graph);
            }
          }
        }
      }
    }
    else exit(EXIT_FAILURE);
  }
  heap_delete(&t); // 1 opé
  return 0;
}
