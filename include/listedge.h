#ifndef LIST_H
#define LIST_H
#include "divers.h"
#include "edge.h"

typedef struct maillon_edge {
  edge_t val;
  struct maillon_edge * next;
}maillon_edge_t,* listedge_t;

//Protoype des fonctions realisant les opérations essentielles du type abstrait Liste

// Crée une liste vide
listedge_t listedge_new() ;

// Retourne VRAI si l est une liste vide
int listedge_is_empty(listedge_t l);

// Ajoute l'élément e en tête de la liste et retourne la nouvelle liste
listedge_t listedge_add_first(edge_t e, listedge_t l);

// Supprime le maillon en tête de liste et retourne la nouvelle liste
// PRECONDITION : liste non vide
listedge_t listedge_del_first(listedge_t l);

// Retourne le nombre d'éléments (ou de maillons) de la liste
int listedge_length(listedge_t l);

// Retourne un pointeur sur le premier maillon contenant e,
// ou NULL si e n'est pas dans la liste
listedge_t listedge_find(edge_t e, listedge_t l);

// Affiche la liste
void listedge_print(listedge_t l);

// Libère toute la liste et retourne une liste vide
listedge_t listedge_delete(listedge_t l);

// Compte le nombre de e dans la liste
int listedge_count(edge_t e, listedge_t l) ;

// Ajoute en fin de liste
listedge_t listedge_add_last(edge_t e, listedge_t l) ;

#endif
