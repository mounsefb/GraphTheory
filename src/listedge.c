// Fichier listedge.c
#include "listedge.h"
#define NIL NULL

listedge_t listedge_new() {
  return NIL;
}

int listedge_is_empty( listedge_t l ) {
  return NIL == l;
}

// Precondition : listedge non vide
edge_t listedge_first(listedge_t l){
  assert(!listedge_is_empty(l));
  return l->val;
}

listedge_t listedge_add_first( edge_t e, listedge_t l ) {
  //puts("ouilist");
  listedge_t p = calloc( 1, sizeof( *p ) );
  if ( NULL == p ) {
    fprintf( stderr, "Fatal: Unable to allocate new listedge link.\n" );
    return l;
  }
  p->val  = e;
  p->next = l;
  return p;
}

// Precondition : listedgee non vide
listedge_t listedge_del_first( listedge_t l ) {
  assert(!listedge_is_empty(l));

  listedge_t p = l->next;
  free( l );
  return p;
}

void listedge_print(listedge_t l) {
  listedge_t p;
  printf("(");
  for ( p=l; ! listedge_is_empty(p); p = p->next) {
    printf("["); edge_print( & p->val ); printf("]");
  }
  printf(")\n");
}

int listedge_length(listedge_t l) {
  int len = 0;
  listedge_t p;
  for( p=l; ! listedge_is_empty(p) ; p=p->next ) {
    len ++;
  }
  return len;
}

listedge_t listedge_find(edge_t e, listedge_t l) {
  listedge_t p;
  for( p=l; ! listedge_is_empty(p) ; p=p->next ) {
    if( edge_equal(&(p->val), &e) ) {
      return p;
    }
  }
  return NULL;
}

int listedge_count(edge_t e, listedge_t l) { int nb=0;
  // TODO : compter les evenements e
  maillon_edge_t * p=l;
  assert(! listedge_is_empty(l));
  while (p!=NULL){
    if (edge_equal(&e, &(p->val))){
      nb+=1;
    }
    p=p->next;
  }
  return nb;
}

listedge_t listedge_add_last(edge_t e, listedge_t l) {
    // TODO : ajouter e en fin de liste l
    if (listedge_is_empty(l)) {
      l=calloc(1, sizeof(*l));
      l->val=e;
      l->next=NULL;
      return l;
    }
    int len=listedge_length(l);
    maillon_edge_t * p=l;
    while (p->next!=NULL){
      p=p->next;
    }
    p=calloc(1, sizeof(*p));
    if(p==NULL) {
      printf("echec calloc\n");
      exit(1);
    }
    p->val=e;
    p->next=NULL;
    maillon_edge_t * p1=l;
    int i=0;
    while(i<len-1){
      p1=p1->next;
      i+=1;
    }
    p1->next=p;
    return l;
}

listedge_t listedge_delete(listedge_t l) {
    // TODO : supprimer tous les maillons de la liste
    maillon_edge_t *p=l;
    while (p!=NULL) {
      p=listedge_del_first(p);
    }
    return NIL;
}
