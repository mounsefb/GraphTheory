#include "dfs.h"

// Algorithme Depth Fisrt Search OU DFS
int DFS(int depart, int arrivee, graph_t* graphe) { // La fonction prend en entrée un sommet de départ, un sommet d'arrivée et un pointeur vers un graphe
    listedge_t arc;
    if(depart==arrivee){
      return 1;
    }
    //printf("oui");
    if(!graphe->initialise) {
      int i;
      for (i = 0; i < graphe->size_vertex; i++) { //Parcours de tous les sommets du graphe à l'aide d'une boucle
        graphe->data[i].pcc = LONG_MAX; //Sinon, son coût est initialisé à une valeur INFINI
      }
      graphe->data[depart].pcc = 0;
      graphe->initialise=1;
    }
    int trouve = 0;
    double DistTemp;
    for (arc = graphe->data[depart].edges; arc != NULL; arc = arc->next) {
      DistTemp = graphe->data[depart].pcc + arc->val.cout;
      if (DistTemp < graphe->data[arc->val.arrivee].pcc) {
        graphe->data[arc->val.arrivee].pcc = DistTemp;
        graphe->data[arc->val.arrivee].plusproche=depart; // 1 opé
        trouve += DFS(arc->val.arrivee, arrivee, graphe);
      }
    }
    return trouve;
}
