#include "heap.h"

heap_t heap_new(int m) {
  //TODO : allocation d'un tas de m elements
  heap_t heap;
  heap.number=0;
  heap.max_size=m;
  heap.data=calloc(m, sizeof(int)); // O(m) pire des cas/ O(mlog(m)) meilleur des cas
  if(heap.data==NULL) exit(EXIT_FAILURE);
  return heap;
}


int heap_add(int valeur, heap_t* ptas) {
  //TODO
  // Ajoute l'element valeur a *ptas
  // Met cet elemetn en derniere position
  // Remonte cet element en respectant l'ordre patiel
  ptas->data[ptas->number]=valeur;
  ptas->number++;
  int i=ptas->number-1, inter;
  while(i!=0 && ptas->data[i]>ptas->data[HEAP_FATHER(i)]){
    inter=ptas->data[i];
    ptas->data[i]=ptas->data[HEAP_FATHER(i)];
    ptas->data[HEAP_FATHER(i)]=inter;
    i=HEAP_FATHER(i);
  }
  return 1;
}

int heap_add_graph(int valeur, heap_t* ptas, graph_t graph) {
  //TODO
  // Ajoute l'element valeur a *ptas
  // Met cet elemetn en derniere position
  // Remonte cet element en respectant l'ordre patiel
  ptas->data[ptas->number]=valeur;
  ptas->number++;
  int i=ptas->number-1, intermed, tmp;
  intermed=heap_verification_graph(*ptas, graph);
  while (intermed >= 0){
    *ptas=heap_resort(intermed,*ptas, graph);
    intermed=heap_verification_graph(*ptas, graph);
  }
  return intermed;
}

int heap_get_max(heap_t tas) {
  //TODO :
  // Retourne la racine sans modifier le tas.
  if (tas.number == 0) return -1;
  return tas.data[0];
}

int heap_get_min(heap_t* tas) {
  if (tas == NULL || tas->number == 0) return -1;
  return tas->data[0];
}

void swap(heap_t* tas, int i, int j) {
  if (tas == NULL || tas->data == NULL || i < 0 || i >= tas->number || j < 0 || j >= tas->number) return;
  int tmp = tas->data[i];
  tas->data[i] = tas->data[j];
  tas->data[j] = tmp;
}

void swap_graph(heap_t* tas, int i, int j, graph_t graph) {
  if (tas == NULL || tas->data == NULL || i < 0 || i > tas->number || j < 0 || j > tas->number) return;
  int tmp = tas->data[i];
  tas->data[i] = tas->data[j];
  tas->data[j] = tmp;
  graph.data[tas->data[i]].indiceTas=i;
  graph.data[tas->data[j]].indiceTas=j;
}

heap_t heap_resort(int aTrier, heap_t tas, graph_t graph) { // O(n) dans le pire des cas / O(1) sinon
  int i=aTrier;
  if (i < 0 || i >= tas.number || tas.data == NULL ) return tas;
    if(HEAP_FATHER(i)>=0 && graph.data[tas.data[HEAP_FATHER(i)]].pcc > graph.data[tas.data[i]].pcc){
      swap_graph(&tas, i, HEAP_FATHER(i), graph);
    }
    else if(HEAP_LEFTSON(i)<tas.number && graph.data[tas.data[HEAP_LEFTSON(i)]].pcc < graph.data[tas.data[i]].pcc){
      swap_graph(&tas, i, HEAP_LEFTSON(i), graph);
    }
    else if(HEAP_RIGHTSON(i)<tas.number && graph.data[tas.data[HEAP_RIGHTSON(i)]].pcc < graph.data[tas.data[i]].pcc){
      swap_graph(&tas, i, HEAP_RIGHTSON(i), graph);
    }
  return tas;
}

int heap_get_position(heap_t tas,int aLocaliser){ // O(n) opérations / 1 sinon
  if(!heap_is_empty(tas)){
    int i=0;
    while(i<tas.max_size && tas.data[i]!=aLocaliser){ // n opérations dans le pire des cas / 1 sinon
      i++;
    }
    return i;
  }
  return 0;
}


int heap_largest_son(heap_t tas, int indice) {
  //TODO :
  // Retourne l'indice du plus grand fils de l'element
  // d'indice indice
  if (tas.data[HEAP_LEFTSON(indice)]<tas.data[HEAP_RIGHTSON(indice)]){
    return HEAP_RIGHTSON(indice);
  }
  return HEAP_LEFTSON(indice);
}

int heap_largest_son_graph(heap_t tas, int indice, graph_t graph) {
  //TODO :
  // Retourne l'indice du plus grand fils de l'element
  // d'indice indice
  if (graph.data[tas.data[HEAP_LEFTSON(indice)]].pcc>graph.data[tas.data[HEAP_RIGHTSON(indice)]].pcc){
    return HEAP_RIGHTSON(indice);
  }
  return HEAP_LEFTSON(indice);
}

int heap_delete_max(heap_t* ptas) {
  // TODO : supprime la racine de *ptas
  // Remplace la racine par le dernier element du *ptas
  // Descend cette nouvelle racine en respectant l'ordre partiel
  int number=ptas->number;
  if(number==0){
    return 0;
  }
  if(number==1){
    ptas->data[0]=0;
  }
  else{
  ptas->data[0]=ptas->data[number-1];
  ptas->data[number-1]=0;
  int i=0, largest_son, leftson=HEAP_LEFTSON(i), rightson=HEAP_RIGHTSON(i), ok=0;
  while (leftson<ptas->number && rightson<ptas->number && ok==0){
    largest_son=heap_largest_son(*ptas, i);
    if(ptas->data[i]>ptas->data[largest_son]){
      swap(ptas, largest_son, i);
      i=largest_son;
    }
    else ok=1;
    leftson=HEAP_LEFTSON(i), rightson=HEAP_RIGHTSON(i);
  }
  }
  return 1;
}

int heap_delete_max_graph(heap_t* ptas, graph_t graph) { // O(n) dans le pire des cas / O(1) sinon
  // TODO : supprime la racine de *ptas
  // Remplace la racine par le dernier element du *ptas
  // Descend cette nouvelle racine en respectant l'ordre partiel
  int number=ptas->number;
  if(number==0){
    return 0;
  }
  if(number==1){
    ptas->data[0]=0;
    ptas->number--;
  }
  else{
  ptas->data[0]=ptas->data[number-1];
  ptas->data[number-1]=0;
  ptas->number--;
  *ptas=heap_resort(0, *ptas,graph);
  }
  return 1;
}


void heap_delete(heap_t* ptas) {
  // TODO : libere la memoire du tas *ptas
  free(ptas->data); // 1 opé
}

int heap_is_empty(heap_t tas) {
  return tas.number==0;
}

// Verifie si l'ordre partiel est bien respecte dans le tas.
int heap_verification(heap_t tas) {
  int i;
  for (i=0; i< tas.number/2; i++) {
  if (tas.data[i]<tas.data[HEAP_LEFTSON(i)]) return i;
    if (HEAP_RIGHTSON(i)<tas.number && tas.data[i]<tas.data[HEAP_RIGHTSON(i)]) return i;
  }
  return -1;
}

int heap_verification_graph(heap_t tas, graph_t graph) {
  int i;
  for (i=0; i<tas.number/2; i++) {
    if (HEAP_LEFTSON(i)<tas.number && graph.data[tas.data[i]].pcc>graph.data[tas.data[HEAP_LEFTSON(i)]].pcc){
      return i;
    }
    if (HEAP_RIGHTSON(i)<tas.number && graph.data[tas.data[i]].pcc>graph.data[tas.data[HEAP_RIGHTSON(i)]].pcc){
      return i;
    }
  }
  return -1;
}

// Affiche le tas
void heap_print_graph(heap_t tas, graph_t graph) {int i;
  for (i=0; i<tas.number; i++)
    printf("%d (%lf), ", tas.data[i], graph.data[tas.data[i]].pcc);
  puts("");
}

void heap_print(heap_t tas) {int i;
  for (i=0; i<tas.number; i++)
    printf("%d, ", tas.data[i]);
  puts("");
}

heap_t heap_insert(int valeur, double cle, heap_t tas, graph_t graph) { // O(n) dans le pire des cas / O(1) sinon
  if (tas.number == tas.max_size) { // 1 opé
    fprintf(stderr, "Erreur : tas plein\n");
    exit(EXIT_FAILURE);
  }
  tas.data[tas.number] = valeur; // 1 opé
  tas.number++; // 1 opé
  int i=tas.number-1;
  while (i != 0 && cle < graph.data[tas.data[HEAP_FATHER(i)]].pcc) { // n itération dans le pire des cas / 0 dans le meilleur
    swap(&tas, i, HEAP_FATHER(i)); // 5 opés
    i = HEAP_FATHER(i); // 1 opé
  }
  return tas;
}
