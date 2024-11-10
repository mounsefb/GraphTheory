
#ifndef _GRAPH
#define  _GRAPH
#include "vertex.h"
#include "divers.h"

typedef char* cle_t;
typedef int value_t;

typedef struct {
  cle_t cle;
  value_t value;
} element_t;

typedef struct _link {
  element_t val;      // un élément de la liste
  struct _link *next; // l'adresse du maillon suivant
} linkhash_t, *listhash_t;    // les structures de maillon et de liste

typedef struct {
  int size;     // nombre de listes de la table
  listhash_t* data; // tableau de listes d'éléments, devant être alloué dynamiquement
} hashtable_t;

// Le graphe :
typedef struct _graph {
  int size_vertex; // nombre de sommets dans le graphe
  int size_edges; //nombre d'arêtes ou arcs dans le graphe
  int oriente; //indique si le graphe est orienté ou non
  int initialise;
  vertex_t* data; // tableau de sommets contenant les données pour chaque sommet du graphe
} graph_t;

int hashtable_put_graph(cle_t k, value_t v, hashtable_t t, graph_t graph);

graph_t graph_read(char * nom_fichier, int type, hashtable_t * t); //lit les fichiers de données et retourn un graphe initialisé avec ces données
void graph_delete(graph_t graph) ; //libère la mémoire allouée pour le graphe
void graph_print(graph_t graph) ; //affiche le graphe
int graph_generate(unsigned long nbsom,unsigned long degre,char filename[512]); //génère un graphe aléatoire avec un nombre donné de sommets/degrés pour les tests

#endif
