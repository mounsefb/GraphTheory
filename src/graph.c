#include "graph.h"
#include "edge.h"
#include <limits.h>
#include <math.h>


//fonction permettant de lire un fichier nommé nom_fichier
//et de stocker ses données dans graph_t
graph_t graph_read(char * nom_fichier, int type, hashtable_t * t){
  graph_t graph;
  FILE* f;
  int oriente,numero,nbsommet,nbarete;
  double lat,longi ;
  int numero1, numero2;
  double cout;
  char tmpstring[512] ;
  char station[512], ligne[512];
  f=fopen(nom_fichier,"r");
  if (f==NULL) { printf("Impossible d’ouvrir le fichier\n"); exit(EXIT_FAILURE);}
  /* Lecture de la premiere ligne du fichier : oriente ou non, nombre de sommets et nombre d’aretes */
  fscanf(f,"%d %d %d ",&oriente,&nbsommet,&nbarete);
  graph.oriente=oriente;
  graph.size_vertex=nbsommet;
  graph.size_edges=nbarete;
  graph.initialise=0;
  graph.data=calloc(nbsommet, sizeof(*graph.data));
  if (graph.data==NULL) {
    printf("alloc dyn de tableau de sommets echouee");
    exit(EXIT_FAILURE);
  }
  /* Ligne de texte "Sommets du graphe" qui ne sert a rien */
  fgets(tmpstring,511,f);
  if(type==0){
  while(fscanf(f,"%d %lf %lf %s", &numero, &lat, &longi,ligne)==4){
    /* lecture d’une ligne de description d’un sommet */
    /* on lit d’abord le numero du sommet, sa position et le nom de la ligne ou route */
    /* numero contient alors l’entier ou numero du sommet, lat et longi la position du sommet */
    /* ligne contient le nom de la route ou de la ligne */
    /* Le nom de la station pouvant contenir des séparateurs comme l’espace, on utilise plutot fgets pour lire
    toute la fin de ligne */
    fgets(tmpstring,2,f);
    fgets(station,sizeof(station)-1,f);
    /* fgets a lu toute la ligne, y compris le retour a la ligne. On supprime le caractere ’\n’ qui peut se
    trouver a la fin de la chaine station : */
    if (station[strlen(station)-1]<32) station[strlen(station)-1]=0;
    /* station contient desormais le nom du sommet, espaces eventuels inclus. */
    graph.data[numero].nom=calloc(strlen(station)+1, sizeof(*graph.data[numero].nom));
    if(graph.data[numero].nom==NULL){
      exit(EXIT_FAILURE);
    }
    strcpy(graph.data[numero].nom,station);
    graph.data[numero].ligne=calloc(strlen(station)+1, sizeof(*graph.data[numero].ligne));
    if(graph.data[numero].ligne==NULL){
      exit(EXIT_FAILURE);
    }
    strcpy(graph.data[numero].ligne,ligne);
    graph.data[numero].x=lat;
    graph.data[numero].y=longi;
    graph.data[numero].edges=listedge_new();
    graph.data[numero].pcc=-1;
    graph.data[numero].visited=0;
  }
  }
  else if(type==1){
  while(fscanf(f,"%d %lf %lf %s", &numero, &lat, &longi,ligne)==4){
    /* lecture d’une ligne de description d’un sommet */
    /* on lit d’abord le numero du sommet, sa position et le nom de la ligne ou route */
    /* numero contient alors l’entier ou numero du sommet, lat et longi la position du sommet */
    /* ligne contient le nom de la route ou de la ligne */
    /* Le nom de la station peut contenir des separateurs comme l’espace. On utilise plutot fgets pour lire
    toute la fin de ligne */
    //printf("oui");
    fgets(tmpstring,2,f);
    fgets(station,sizeof(station)-1,f);
    /* fgets a lu toute la ligne, y compris le retour a la ligne. On supprime le caractere ’\n’ qui peut se
    trouver a la fin de la chaine station : */
    if (station[strlen(station)-1]<32) station[strlen(station)-1]=0;
    /* station contient desormais le nom du sommet, espaces eventuels inclus. */
    graph.data[numero].nom=calloc(strlen(station)+1, sizeof(*graph.data[numero].nom));
    if(graph.data[numero].nom==NULL){
      exit(EXIT_FAILURE);
    }
    strcpy(graph.data[numero].nom,station);
    graph.data[numero].ligne=calloc(strlen(station)+1, sizeof(*graph.data[numero].ligne));
    if(graph.data[numero].ligne==NULL){
      exit(EXIT_FAILURE);
    }
    strcpy(graph.data[numero].ligne,ligne);
    graph.data[numero].x=lat;
    graph.data[numero].y=longi;
    graph.data[numero].edges=listedge_new();
    graph.data[numero].pcc=-1;
    graph.data[numero].visited=0;
    hashtable_put_graph(graph.data[numero].nom, numero, *t, graph);
    }
  }
  /*Pour sauter les lignes de commentaires, on peut simplement utiliser la fonction fgets, sans exploiter
  la chaine de caracteres lue dans le fichier */
  fgets(tmpstring,511,f);
  edge_t e;
  if(oriente==1){
    while(fscanf(f,"%d %d %lf", &numero1, &numero2, &cout)==3){
        e.depart=numero1;
        e.arrivee=numero2;
        e.cout=cout;
        graph.data[numero1].edges=listedge_add_first(e, graph.data[numero1].edges);
    }
  }
  else {
    while(fscanf(f,"%d %d %lf", &numero1, &numero2, &cout)==3){
        e.depart=numero1;
        e.arrivee=numero2;
        e.cout=cout;
        graph.data[numero1].edges=listedge_add_first(e, graph.data[numero1].edges);
        e.depart=numero2;
        e.arrivee=numero1;
        graph.data[numero2].edges=listedge_add_first(e, graph.data[numero2].edges);
    }
  }
  /* Ne pas oublier de fermer votre fichier */
  fclose(f);
  return graph;
}

//fonction permettant d'afficher un graph
//cette fonction affichera le nombre de sommet, le nombre d'arrete
//et le tableau des sommets avec les différents arcs
void graph_print(graph_t graph){
  printf("NbreSommet = %d, NbreArete = %d \n", graph.size_vertex, graph.size_edges);
  int i;
  for (i=0; i<graph.size_vertex; i++){
    printf("--------------------------------------------------------------- \n");
    printf("infos sommet n° %d :\n", i);
    vertex_print(&graph.data[i]);
  }
}

//fonction qui libére le tableau alloué dynamiquement de sommets
void graph_delete(graph_t graph){
  int i;
  for (i=0; i<graph.size_vertex; i++){
    free(graph.data[i].nom);
    free(graph.data[i].ligne);
    listedge_delete(graph.data[i].edges);
  }
  free(graph.data);
}


double sqr(double x) {return x*x; }

int graph_generate(unsigned long nbsom,unsigned long degre,char filename[512]) {
  FILE* fp;
  int taille=1000;
  unsigned long i,j;

  double* sommetsx=calloc(nbsom,sizeof(*sommetsx));
  double* sommetsy=calloc(nbsom,sizeof(*sommetsy));
  if (sommetsx==NULL|| sommetsy==NULL) { printf("Erreru allocation\n"); return 0; }
  fp=fopen(filename,"w");
  if(fp==NULL) return 0;
  fprintf(fp,"0 %lu %lu\n",nbsom,degre*nbsom);
  fprintf(fp,"Sommets du graphe \n");
  for (i=0; i<nbsom; i++) {
    sommetsx[i]=random()/(double)INT_MAX*(double)taille;
    sommetsy[i]=random()/(double)INT_MAX*(double)taille;
    fprintf(fp,"%lu %lf %lf route sommet%lu\n",i,sommetsx[i],sommetsy[i], i);
  }
  fprintf(fp,"arc du graphe : départ arrivée valeur\n");
  for (i=0; i<nbsom;i++) {
    for (j=0; j<degre; j++) { int k,l=0;
      double d=0;
      do { k=random()%nbsom;
        d=taille/100*exp(sqr((random()/(double)RAND_MAX))*(1.+l/100)) ;
        l++;
      } while (k==i || hypot(sommetsx[i]-sommetsx[k],sommetsy[i]-sommetsy[k])> d);
      fprintf(fp,"%lu %d %lf\n",i,k,hypot(sommetsx[i]-sommetsx[k],sommetsy[i]-sommetsy[k]));
    }
  }
  fclose(fp);
  free(sommetsx);
  free(sommetsy);
  return 1;
}
