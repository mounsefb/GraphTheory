#include "listhash.h"

int listhash_is_empty(listhash_t l){
  return l==NULL;
}

listhash_t listhash_add_first_graph(int res, element_t e, hashtable_t hash, graph_t graph){
  listhash_t p = calloc( 1, sizeof( *p ) );
  if ( NULL == p ) {
    fprintf( stderr, "Fatal: Unable to allocate new listedge link.\n" );
    return hash.data[res];
  }
  p->val  = e;
  p->next = hash.data[res];
  return p;
}

listhash_t listhash_add_first(int res, element_t e, hashtable_t hash){
  if(listhash_find(e.cle, hash.data[res])) return hash.data[res];
  listhash_t p = calloc( 1, sizeof( *p ) );
  if ( NULL == p ) {
    fprintf( stderr, "Fatal: Unable to allocate new listedge link.\n" );
    return hash.data[res];
  }
  p->val  = e;
  p->next = hash.data[res];
  return p;
}

listhash_t listhash_find(cle_t k, listhash_t l){
  listhash_t p;
  for( p=l; ! listhash_is_empty(p) ; p=p->next ) {
    //printf("%d\n",strcmp(p->val.cle,k)%32);
    if( strcasecmp(p->val.cle,k) == 0) {
      return p;
    }
  }
  return NULL;
}

int listhash_find_list(cle_t k, listhash_t l, listhash_t * find){
  listhash_t p;
  listhash_t r=NULL;
  for( p=l; ! listhash_is_empty(p) ; p=p->next ) {
    if( strcmp(p->val.cle,k) == 0) {
      listhash_t q = calloc( 1, sizeof( * q) );
      if ( NULL == q ) {
        fprintf( stderr, "Fatal: Unable to allocate new listedge link.\n" );
        return 0;
      }
      q->val  = p->val;
      q->next = r;
      r=q;
    }
  }
  *find=r;
  return 1;
}

void listhash_print(listhash_t l) {
  listhash_t p;
  printf("(");
  for ( p=l; ! listhash_is_empty(p); p = p->next) {
    printf("["); element_print( p->val ); printf("]");
  }
  printf(")\n");
}

listhash_t listhash_del_first( listhash_t l ) {
  assert(!listhash_is_empty(l));
  listhash_t p = l->next;
  free( l );
  return p;
}

listhash_t listhash_delete(listhash_t l){
  linkhash_t *p=l;
  while (p!=NULL) {
    p=listhash_del_first(p);
  }
  return NULL;
}
