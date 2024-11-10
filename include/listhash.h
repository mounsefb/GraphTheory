#ifndef LIST_H
#define LIST_H
#include "divers.h"
#include "elementhash.h"
#include "edge.h"

typedef struct _link {
  element_t val;      // un élément de la liste
  struct _link *next; // l'adresse du maillon suivant
} linkhash_t, *listhash_t;    // les structures de maillon et de liste

typedef struct {
  int size;     // nombre de listes de la table
  listhash_t* data; // tableau de listes d'éléments, devant être alloué dynamiquement
} hashtable_t;

//////////////////////////////////////////////


typedef struct maillon_edge {
  edge_t val;
  struct maillon_edge * next;
}maillon_edge_t,* listedge_t;


typedef
  struct {
    char* nom;    //  Nom donne au sommet
    char* ligne;  // Nom de la route ou de la ligne
    listedge_t edges; // Liste des arcs partant de ce sommmet
    double x,y;   // Position du sommet
    double pcc;   // valeur du chemin du depart a ce sommet
    int visited;
    int indiceTas;
    int hash;
  } vertex_t;


typedef struct _graph {
  int size_vertex;
  int size_edges;
  vertex_t* data; } graph_t;

  //////////////////////////////////////////////////////

//Protoype des fonctions realisant les opérations essentielles du type abstrait Liste

// Retourne VRAI si l est une liste vide
int listhash_is_empty(listhash_t l);

// Ajoute l'élément e en tête de la liste et retourne la nouvelle liste
listhash_t listhash_add_first_graph(int res,  element_t e, hashtable_t hash, graph_t graph);

listhash_t listhash_add_first(int res,  element_t e, hashtable_t hash);

// Retourne un pointeur sur le premier maillon contenant e,
// ou NULL si e n'est pas dans la liste
listhash_t listhash_find(cle_t k, listhash_t l);

int listhash_find_list(cle_t k, listhash_t l, listhash_t *find);

// Affiche la liste
void listhash_print(listhash_t l);

// Libère toute la liste et retourne une liste vide
listhash_t listhash_delete(listhash_t l);

listhash_t listhash_del_first( listhash_t l );

#endif
