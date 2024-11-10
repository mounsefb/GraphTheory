#ifndef _VERTEX_H
#define  _VERTEX_H
#include "listedge.h"
#include "divers.h"

// Un sommet
typedef
  struct {
    char* nom;    //  Nom donne au sommet
    char* ligne;  // Nom de la route ou de la ligne
    listedge_t edges; // Liste des arcs partant de ce sommmet
    double x,y;   // Position du sommet
    double pcc;   // valeur du chemin du depart a ce sommet
    int plusproche;
    int visited;
    int indiceTas;
  } vertex_t;

void vertex_print(vertex_t *e) ;

#endif
