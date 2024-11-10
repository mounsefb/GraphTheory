#include "heap.h"

#define NBTEST 100

int main() { int i;
  int x=1;
  heap_t tas;
  tas=heap_new(NBTEST);

  for (i=0; i<NBTEST; i++) {
    switch(random()%2) {
      case 0:  x=random()%NBTEST;
        printf("Ajout de "); printf("%d",x);
        puts("");
        if (!heap_add(x,&tas)) {
          printf("Pas assez de memoire pour ajouter un element\n");
          exit(EXIT_FAILURE);
        }
        printf("Nouveau tas : ");
        heap_print(tas);
        puts("---------------");
        break;
      case 1:
        if (heap_is_empty(tas)) { printf("Tas vide: rien a supprimer\n"); break;}
        printf("Suppression de la racine :");
        puts("");
        x=heap_get_max(tas);
        heap_delete_max(&tas);
        printf("Nouveau tas : ");
        heap_print(tas);
        puts("---------------");
        break;
      }
      //printf("verif=%d\n", heap_verification(tas) );
      if (!heap_verification(tas)) {
        printf("Erreur : ce n'est pas un tas \n");
        exit(EXIT_FAILURE);
      }
    }
    heap_delete(&tas);
    return EXIT_SUCCESS;
  }
