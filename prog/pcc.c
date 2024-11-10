#include "graph.h"
#include "divers.h"
#include "bfs.h"
#include "dfs.h"
#include "Dijkstra.h"
#include "hash.h"

#define INFINI DBL_MAX

int reconstructionDijkstra(int arrivee, int depart, int * tab, int k, graph_t graph) {
  if (arrivee==depart) return 1;
  else {
     tab[k]=graph.data[arrivee].plusproche;
     k++;
     if(reconstructionDijkstra(graph.data[arrivee].plusproche, depart, tab, k, graph)){
       return 1;
     }
  }
  return 0;
}

int main(int argc, char**argv) {
  char type=0;        // Type de l'algorithme (Dijstra:0, BFS:1, DFS:2)
  char verbose=0;     // Affichage du chemin ou non
  int depart, arrivee;// Numero des sommets de depart et arrivee
  graph_t graph;     // Variable contenant le graph
  clock_t cl;         // Variable pour mesurer le temps
  int i;

    // Verification du nombre d'arguments sur la ligne de commande
  if (argc!=5 && argc!=6) {
    printf("Usage : %s graph.txt type(0..2) depart arrivee [-v]\n",argv[0]);
    exit(EXIT_FAILURE);
  }
    // Conversion du type d'algo en nombre et Verification du type de l'algo
  type= atoi(argv[2]);
  if (type<0 || type >2) {
    printf("Erreur algorithme\n"); exit(EXIT_FAILURE);
  }
  if(argv[3][0]>=48 && argv[3][0]<=57 ){
      // Conversion du numero de sommet de depart en nombre
    depart = atoi(argv[3]);
      // Conversion du numero de sommet d'arrivee en nombre
    arrivee = atoi(argv[4]);
    graph = graph_read(argv[1], 0, NULL);
  }
  else exit(EXIT_FAILURE);
  listedge_t arc;
  edge_t e;
  //listedge_print(graph.data[depart].edges);
  for (arc = graph.data[depart].edges; arc != NULL; arc = arc->next){
    if (!strcmp(graph.data[arc->val.arrivee].nom, graph.data[depart].nom)){
      //arc->val.cout=0;
      e.depart=depart;
      e.arrivee=arc->val.arrivee;
      e.cout=0;
      graph.data[depart].edges=listedge_add_first(e, graph.data[depart].edges);
      e.depart=arc->val.arrivee;
      e.arrivee=depart;
      graph.data[arc->val.arrivee].edges=listedge_add_first(e, graph.data[arc->val.arrivee].edges);
    }
  }

  //listedge_print(graph.data[depart].edges);
  for (arc = graph.data[arrivee].edges; arc != NULL; arc = arc->next){
    if (!strcmp(graph.data[arc->val.arrivee].nom, graph.data[arrivee].nom)){
      //arc->val.cout=0;
      e.depart=arrivee;
      e.arrivee=arc->val.arrivee;
      e.cout=0;
      graph.data[arrivee].edges=listedge_add_first(e, graph.data[arrivee].edges);
      e.depart=arc->val.arrivee;
      e.arrivee=arrivee;
      graph.data[arc->val.arrivee].edges=listedge_add_first(e, graph.data[arc->val.arrivee].edges);
    }
  }
  graph.initialise=0;
    // Affichage du chemin ou non
  if (argc==6) verbose=1;

    // TODO :
    // Lecture du fichier graph. Si echec de lecture, sortie du programme
    //Gestion d'erreur contenue dans la fonction
    // Test de la validite du somment de depart. Sortie du programme si mauvais numero.
  if (depart <0 || depart >= graph.size_vertex) {
    printf("Le sommet de depart n'existe pas \n");  exit(EXIT_FAILURE);
  }
    // Test de la validite du somment d'arrivee. Sortie du programme si mauvais numero.
  if (arrivee<0 || arrivee>= graph.size_vertex) {
    printf("Le sommet d'arrivee n'existe pas \n");  exit(EXIT_FAILURE);
  }

  printf("Valeur du PCC de %s entre %s et %s : ", argv[1],graph.data[depart].nom,graph.data[arrivee].nom);

    // Heure de debut de l'appel de la fonction de calcul du plus court chemin
  cl=clock();
    //
  switch (type) {
    case 0 :
    // TODO :
      // Appel a la recherche de PCC par dijkstra
      // Sortie du programme si probleme allocation memoire.
      Dijkstra_like(depart, arrivee, graph);
      break;
    case 1 :
      // TODO :
      // Appel a la recherche de PCC par BFS
      // Sortie du programme si probleme allocation memoire.
      ParcoursEnLargeur(depart, arrivee, graph);
      //graph_print(graph);
      break;
    case 2 :
      // TODO :
      // Appel a la recherche de PCC par DFS
      // Sortie du programme si probleme allocation memoire.
      DFS(depart, arrivee, &graph);
      break;
    default : break;
  }
    // calcul de la duree de l'execution de la fonction de calcul du plus court chemin
  cl=clock()-cl;

    // Le plus court chemin existe t il ?
    // La valeur DBL_MAX est l'initialisation des chemins
  if (graph.data[arrivee].pcc != LONG_MAX) {
      // Affichage de la valeur de ce plus court chemin
    printf("%lf\n",graph.data[arrivee].pcc);
      // Affichage du chemin si besoin
    if (verbose) {
      printf("Chemin parcouru\n");
      int * tab;
      tab=calloc(graph.size_vertex,sizeof(int));
      if(tab==NULL) {
        printf("alloc echouee \n");
        exit(EXIT_FAILURE);
      }
      for(i=0; i<graph.size_vertex; i++) tab[i]=INT_MAX;
      if(!reconstructionDijkstra(arrivee, depart, tab, 0, graph)){
        for(i=0; i<graph.size_vertex; i++) printf("%d, ", tab[i]);
        printf("reconstruction echouee \n");
        exit(EXIT_FAILURE);
      }
      int k=0;
      while(k<graph.size_vertex && tab[k]!=INT_MAX ){
        k++;
      }
        printf("%s pcc %.2f", graph.data[depart].nom, graph.data[depart].pcc);
        puts("");
        for(i=k-2; i>=0; i--) {
          if(i<k-2 && i!=0 && ! strcmp(graph.data[tab[i]].nom,graph.data[tab[i+1]].nom) && strcmp(graph.data[depart].nom,graph.data[tab[i]].nom) && strcmp(graph.data[arrivee].nom,graph.data[tab[i]].nom)){
            printf("Correspondance a %s pcc %.2lf, prendre la ligne %s\n", graph.data[tab[i]].nom, graph.data[tab[i]].pcc, graph.data[tab[i-1]].ligne);
            }
          else if (strcmp(graph.data[depart].nom,graph.data[tab[i]].nom) && strcmp(graph.data[arrivee].nom,graph.data[tab[i]].nom)){
            printf("%s pcc %.2f", graph.data[tab[i]].nom, graph.data[tab[i]].pcc);
            puts("");
          }
        }
        printf("%s pcc %.2f", graph.data[arrivee].nom, graph.data[arrivee].pcc);
        puts("");
      free(tab);
    }
  }
  else printf("Chemin impossible\n");

    // TODO :
    // liberation de l'allocation memoire du graph
  graph_delete(graph);
  return EXIT_SUCCESS;
}
