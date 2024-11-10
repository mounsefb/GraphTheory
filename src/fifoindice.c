#include <stdio.h>
#include <stdlib.h>
#include "fifoindice.h"

fifoint_t fifoint_new(void){ // création d'une nouvelle liste vide en retournant un pointeur nul
  return NULL;	/* la liste vide est representée par NULL	*/
}

int fifoint_is_empty(fifoint_t L) //Vérifie si la liste est vide ou non en comparant le pointeur à NULL
{	return L==NULL;	/* la liste vide est representée par NULL	*/
}

void fifoint_print(fifoint_t L) {
  //affiche tous les elements de la file
  if (fifoint_is_empty(L)){
    printf("()");
    return;
  }
  fifoint_t p=L->next;
  printf("(");
  do{
    printf("[");
    printf("%d", (p->val));
    p=p->next;
    printf("]");
  }while (p!=L->next); // parcoure la liste à partir de son premier élément
  printf(")");
  puts("");
}

fifoint_t fifoint_enqueue(int e, fifoint_t f){ //ajoute un entier à la fin de la file
  fifoint_t c=calloc(1, sizeof(*c));
  // ajoute le int a la queue de la file
  if(c==NULL){
    printf("alloc échouée");
    return NULL;
  }
  c->val=e; //1 opération
  if(fifoint_is_empty(f)){ //1 opération + 1 appel de fonction
    c->next=c; // 1 opéaration
    return c;
  }
  c->next=f->next; // 1 opéaration
  f->next=c; // 1 opéaration
  return c;
}

int fifoint_peek(fifoint_t f){
  // retourne le int en tete de file sans le supprimer
  return f->next->val;
}

fifoint_t fifoint_del_head(fifoint_t f) { // 5 opérations
  // supprime le int en tete de file et retourne la nouvelle file
  if (fifoint_is_empty(f)){
    return NULL;
  }
  if (f->next==f){
    free(f);
    return NULL;
  }
  fifoint_t c=f->next;
  f->next=f->next->next;
  free(c);
  return f;
}


int fifoint_dequeue(fifoint_t* af) { int e;
  // retourne le int en tete de file ET le supprime de la file.
  e=fifoint_peek(*af);
  *af=fifoint_del_head(*af);
  return e;
}

fifoint_t fifoint_delete(fifoint_t f) {
  // supprime tous les maillons de la file
  while (f!=NULL){
    fifoint_dequeue(&f);
  }
  return fifoint_new();
}
