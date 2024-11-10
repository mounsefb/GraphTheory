#include "graph.h"
#include "time.h"
#include "bfs.h"
#include "dfs.h"
#include "Dijkstra.h"

// Nom du fichier contenant les graphes avec XX sommets
#define FIC_GRAPHE "graphe_tmp.txt"
// Nom du fichier contenant les temps des 3 algos
#define FIC_RES "Temps_PCC.csv"
// Nombre de sommets de depart
#define NB_SOMMET_DEPART 10
// Nombre de sommets d'arrivee
#define NB_SOMMET_ARRIVEE NB_SOMMET_DEPART

int graph_generate(unsigned long nbsom,unsigned long degre,char filename[512]);

int main(int argc, char**argv) {
  graph_t graphe; // Le graphe
  clock_t cl;     // Pour mesurer le temps d'une fonction
  // Les numeros aleatoires des sommets de depart et arrivee
  int depart[NB_SOMMET_DEPART], arrivee[NB_SOMMET_ARRIVEE];
    // StopDFS est utilise quand DFS commence a prendre trop de Temps
    // On ne teste plus son utilisation
  int stopDFS=0;
  int i,j;
  unsigned long nb_sommets_max,degre,k;
  FILE* fp;
    // Comment utiliser le programme
  if (argc !=3) {
    printf("Usage : %s nb_sommets_max degre\n",argv[0]);
    exit(EXIT_FAILURE);
  }
    // Le nombre de sommets maximal a tester
  nb_sommets_max=atoi(argv[1]);
  if (nb_sommets_max<0) { printf("nb_sommets_max >0\n"); exit(EXIT_FAILURE);  }

    // Le degre des sommets
  degre=atoi(argv[2]);
  if (degre<0) { printf("nb_sommets_max >0\n"); exit(EXIT_FAILURE); }

    // Ouverture du fichier contenant les temps CPU des 3 algos
  if ( (fp=fopen(FIC_RES,"w"))==NULL) {
    printf("Impossible d'ouvrir le fichier de resultat %s \n",FIC_RES);
    exit(EXIT_FAILURE);
  }

  srandom(getpid());
    // On teste des graphes dont le nombre de sommets va de 10 à nb_sommets_max,
    // en doublant ce nombre a chaque etape
  for (k=10; k<nb_sommets_max; k*=2) {
      // Generation du graphe de k sommets dans un fichier
    printf("Generation du graphe pour %lu sommets\n",k);
    if (graph_generate(k,degre,"graphe_tmp.txt")==0) {
      printf("Erreur generation graphe de %lu sommets avec %lu voisisns\n",k,degre);
      exit(EXIT_FAILURE);
    }
      // Generation des numeros de sommets de depart et d'arrivee
    for (i=0; i<NB_SOMMET_DEPART; i++) depart[i]=random()%k;
    for(j=0; j<NB_SOMMET_ARRIVEE; j++) arrivee[j]=random()%k;

      // TODO :
      // Lecture du fichier qui vient d'etre genere dans la variable graphe
      // **********************
      graphe=graph_read("graphe_tmp.txt", 0, NULL);
      //graph_print(graphe);
      // Debut du test de Dijkstra
      // On initialise de compteur de temps
      // on boucle sur tous 100 chemins a tester
    cl=clock();
    for (i=0; i<NB_SOMMET_DEPART; i++){
      for(j=0; j<NB_SOMMET_ARRIVEE; j++){
          // TODO :
          // Appel a la fonction qui calcule le pcc avec dijkstra
          // entre depart[i] et arrivee[j] sur graphe
          // **********************
          Dijkstra_like(depart[i], arrivee[j], graphe);
      }
    }
      // Fin du compteur de temps
    cl=clock()-cl;
      // Ecriture de temps mis par Dijkstra pour 100 chemins dans le graphe de k sommets
    fprintf(fp,"%lu\t%lf",k,(double)cl/CLOCKS_PER_SEC);
      // Liberation memoire du graphe
    graph_delete(graphe);

      // Meme chose pour BFS
      // TODO :
      // Lecture du fichier qui vient d'etre genere dans la variable graphe
      // **********************
      graphe=graph_read("graphe_tmp.txt", 0, NULL);
      // Debut du test de BFS
      // On initialise de compteur de temps
      // on boucle sur tous 100 chemins a tester
    cl=clock();
    for (i=0; i<NB_SOMMET_DEPART; i++){
      for(j=0; j<NB_SOMMET_ARRIVEE; j++){
          // TODO :
          // Appel a la fonction qui calcule le pcc avec BFS
          // entre depart[i] et arrivee[j] sur graphe
          // **********************
           ParcoursEnLargeur(depart[i], arrivee[j], graphe);
        }
      }
      // Fin du compteur de temps
    cl=clock()-cl;
      // Ecriture de temps mis par BFS pour 100 chemins dans le graphe de k sommets
    fprintf(fp,"\t%lf",(double)cl/CLOCKS_PER_SEC);
    // Liberation memoire du graphe
    graph_delete(graphe);

    // Meme chose pour DFS ou presque
    // COmme il est plus couteux, on ne le teste pas si l'algo devient trop long
    if (!stopDFS) {
      // TODO :
      // Lecture du fichier qui vient d'etre genere dans la variable graphe
      // **********************
      graphe=graph_read("graphe_tmp.txt", 0, NULL);
      // Debut du test de DFS
      // On initialise de compteur de temps
      // on boucle sur tous 100 chemins a tester
      cl=clock();
      for (i=0; i<NB_SOMMET_DEPART; i++){
        for(j=0; j<NB_SOMMET_ARRIVEE; j++){
          // TODO :
          // Appel a la fonction qui calcule le pcc avec DFS
          // entre depart[i] et arrivee[j] sur graphe
          // **********************
          DFS(depart[i], arrivee[j], &graphe);
        }
      }
      // Fin du compteur de temps
      cl=clock()-cl;
      // Si le temps mis est superieur a 5 secondes,
      // on interdit de continuer a tester DFS sur les graphes plus grands
      if ((double)cl/CLOCKS_PER_SEC >=5) stopDFS=1;
      // Ecriture de temps mis par DFS pour 100 chemins dans le graphe de k sommets
      fprintf(fp,"\t%lf",(double)cl/CLOCKS_PER_SEC);
      // Liberation memoire du graphe
      graph_delete(graphe);
    }
      // Fin d'une ligne du fichier des temps CPU
    fprintf(fp,"\n");
  }
    // Fermeture du fichier des temps CPU
  fclose(fp);

    // Affichage des graphes avec gnuplot
  char commande[1024];
    // Affichage avec gnuplot des temps de calcul en fonction du nombre de sommets
  strcat(commande,"set datafile separator ';'");
  sprintf(commande,"gnuplot -p -e \"set logscale x; set title 'PCC pour %lu voisins';",degre);
  strcat(commande,"set xlabel 'Nombre de sommets'; set ylabel 'Temps en secondes';");
  // strcat(commande,"plot '"FIC_RES"' u 1:2 with line lt 4 title 'Dijkstra'");
  strcat(commande,"plot '"FIC_RES"' u 1:2 with line lt 4 title 'Dijkstra'");
  strcat(commande,", '' u 1:3 with line lt 2 title 'BFS' ");
  strcat(commande,", '' u 1:4 with line lt 6 title 'DFS'; quit\"");
  system(commande);
    // Suppression du fichier contenant le graphe aleatoire
  system("rm "FIC_GRAPHE);
  return EXIT_SUCCESS;
}
