#include "hash.h"

hashtable_t hashtable_new(int m){
   hashtable_t hash;
   hash.size=m;
   hash.data=calloc(m, sizeof(listhash_t));
   if (hash.data==NULL){
     printf("alloc hash echouee");
     exit(EXIT_FAILURE);
   }
   return hash;
}

int hashing(cle_t cle, hashtable_t hash){
  int b=21, i=0;
  int resultat=0;
  while(cle[i]!='\0'){
     if (cle[i]>=65 && cle[i]<=90){
       resultat=resultat+(cle[i]+(97-65))*pow(b,i);
     }
     else if (cle[i]>=97 && cle[i]<=122){
      resultat=resultat+cle[i]*pow(b,i);
    }
    resultat=resultat%hash.size;
    if(resultat<0){
      resultat+=hash.size;
    }
    i++;
  }
  return resultat;
}

int hashtable_put(cle_t k, value_t v, hashtable_t hash){
  int res=hashing(k, hash);
  element_t e;
  e.cle=k;
  e.value=v;
  hash.data[res]=listhash_add_first(res, e, hash);
  return 1;
}

int hashtable_put_graph(cle_t k, value_t v, hashtable_t hash, graph_t graph){
  int res=hashing(k, hash);
  element_t e;
  e.cle=k;
  e.value=v;
  hash.data[res]=listhash_add_first_graph(res, e, hash, graph);
  return 1;
}

int hashtable_contains(cle_t k, hashtable_t t){
  int res=hashing(k, t);
  if (listhash_find(k, t.data[res])==NULL){
    return 0;
  }
  return 1;
}

int hashtable_get_value(cle_t k, value_t* pv, hashtable_t t){
  int res=hashing(k, t);
  listhash_t p=listhash_find(k, t.data[res]);
  if(p==NULL){
    return 0;
  }
  *pv=p->val.value;
  return 1;
}

int hashtable_delete_key(cle_t k, hashtable_t t){
  int res=hashing(k, t);
  listhash_t p;
  listhash_t pprime;
  for(p=t.data[res]; !listhash_is_empty(p); p=p->next){
    if(! strcmp(p->val.cle,k)){
      pprime->next=p->next;
      free(p);
      return 1;
    }
    pprime=p;
  }
  return 0;
}

int hashtable_delete(hashtable_t hash){
  for (int i=0; i<hash.size; i++){
    listhash_delete(hash.data[i]);
  }
  free(hash.data);
  return 1;
}

void hashtable_print(hashtable_t hash){
  for(int i=0; i<hash.size; i++){
    printf("-----------------------\n");
    listhash_print(hash.data[i]);
    puts("");
  }
}
