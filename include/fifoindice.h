// fichier fifoint.h pour l'implantation du TAD File au moyen d'une liste chaînée circulaire
#ifndef FIFO_H_
#define FIFO_H_

// 1. le type fifoint_t est défini comme "pointeur sur maillon"
typedef
  struct _fifolink {
    int val; /* un élément de la liste*/
    struct _fifolink *next; /* l'adresse du maillon suivant */
  } * fifoint_t;

// 2. prototypes des fonctions de l'API du TAD File

// Crée et retourne un file vide
fifoint_t fifoint_new();

// Retourne 1 si la file  queue   est vide, 0 sinon
int fifoint_is_empty(fifoint_t queue);

// Ajoute l'élément e à la file  queue  et retourne la nouvelle file
// Retourne NULL en cas d'erreur
fifoint_t fifoint_enqueue(int e, fifoint_t queue);

// Retourne l'élément en tête de file (sans l'enlever de la file)
// PRECONDITION : la file  queue  ne doit pas être vide
int fifoint_peek(fifoint_t queue);

// Enlève l'élément en tête de la file, et retourne la file
// PRECONDITION : la file pointée par  f  ne doit pas être vide
fifoint_t fifoint_del_head(fifoint_t queue);

// Enlève l'élément en tête de la file, et retourne cet élément
// PRECONDITION : la file pointée par  p_queue  ne doit pas être vide
int fifoint_dequeue(fifoint_t * p_queue);
    // Remarque sur le prototype de fifoint_dequeue() :
    // Cette fonction doit "retourner" 2 choses :
    //  - l'élément qui était en tête
    //  - et la file modifiée, dont on enlevée l'ancienne tête
    // Il faut donc, en C, utiliser un passage par adresse pour l'une
    // de ces deux valeurs (ici : la file)

// Détruit la file et retourne une file vide
fifoint_t fifoint_delete(fifoint_t queue);

// FONCTION optionnelle : affiche tous les éléments de la file, dans l'ordre
void fifoint_print(fifoint_t queue);

#endif
