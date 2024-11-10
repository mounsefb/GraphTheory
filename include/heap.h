#ifndef _HEAP
#define _HEAP
#include "divers.h"
#include "graph.h"

typedef
  struct {
    int* data;
    int max_size;
    int number;
  } heap_t;


heap_t heap_new(int m);
int heap_add(int valeur, heap_t* ptas);
int heap_add_graph(int valeur, heap_t* ptas, graph_t graph);
int heap_get_max(heap_t tas);
int heap_get_min(heap_t* tas);
int heap_delete_max(heap_t* ptas);
int heap_delete_max_graph(heap_t* ptas, graph_t graph);
void heap_delete(heap_t* ptas);
heap_t heap_resort(int aTrier, heap_t tas, graph_t graph);
void swap(heap_t* tas, int i, int j);
int heap_is_empty(heap_t tas);
int heap_verification(heap_t tas) ;
int heap_verification_graph(heap_t tas, graph_t graph) ;
void heap_print(heap_t tas) ;
void heap_print_graph(heap_t tas, graph_t graph) ;
heap_t heap_insert(int valeur, double cle, heap_t tas, graph_t graph);
int heap_get_position( heap_t tas, int i);
#define HEAP_FATHER(i) ( ((i)-1)/2)
#define HEAP_LEFTSON(i) ( 2*(i)+1)
#define HEAP_RIGHTSON(i) ( 2*((i)+1))


#endif
