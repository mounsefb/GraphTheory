#include "hash.h"
#include <ctype.h>
#include <string.h>
#include <time.h>

int main(int a, char **b)
{ hashtable_t  histo;
  int n;
  value_t valeur;
  char mot[512];


  printf("Taille de la table ? \n"); scanf("%d",&n);
  histo=hashtable_new(n);

  // Ajout du couple "Phelma",1
  puts("Ajout du couple \"Phelma\",1");
  hashtable_put("Phelma",1,histo);
  printf("Table \n");
  hashtable_print(histo);
  puts("---------------");

  // Ajout du couple "une",3
  puts("Ajout du couple \"une\",3");
  hashtable_put("une",3,histo);
  printf("Table \n");
  hashtable_print(histo);
  puts("---------------");

  // Ajout du couple "ecole",2
  puts("Ajout du couple \"ecole\",2");
  strcpy(mot,"ecole");
  hashtable_put("ecole",2,histo);
  printf("Table \n");
  hashtable_print(histo);
  //hashtable_print(histo);
  puts("---------------");

  //pas deux strcpy d'affilé sinon comme meme adresse,changement des deux noms


  // Recherche de la cle "ecole"
  strcpy(mot,"ecole");
  printf("Recherche du mot %s\n",mot);
  if (hashtable_contains(mot,histo))
     printf ("%s est dans la table\n",mot);
  else
  printf ("%s n'est pas dans la table\n",mot);
  puts("---------------");

  // Recherche de la cle "ensimag"
  strcpy(mot,"ensimag");
  printf("Recherche du mot %s\n",mot);
  if (hashtable_contains(mot,histo))
     printf ("%s est dans la table\n",mot);
  else
  printf ("%s n'est pas dans la table\n",mot);
  puts("---------------");

  // Affichage du mot et de la valeur
  strcpy(mot,"ingénieurs");
  printf("Affichage de la valeur associee au mot %s\n",mot);
  if (hashtable_get_value(mot,&valeur,histo)) {
    printf("%s a pour valeur : %d \n",mot, valeur);
  }
  else {
    printf("%s n'est pas dans la table\n", mot);
  }
  puts("---------------");

  // Affichage du mot et de la valeur
  strcpy(mot,"ecole");
  printf("Affichage de la valeur associee au mot %s\n",mot);
  //hashtable_print(histo);
  if (hashtable_get_value(mot,&valeur,histo)) {
    printf("%s a pour valeur : %d \n",mot, valeur);
  }
  else {
    printf("%s n'est pas dans la table\n", mot);
  }
  puts("---------------");

  //Suppression; A commenter dans un premier temps.

  // Suppresion de l'element de cle  "ingénieurs"
  printf("Suprresion de l'entrée associee au mot %s\n","ingénieurs");
  strcpy(mot,"ingenieurs");
  if(hashtable_delete_key("ingénieurs",histo)==1){
  printf("Table \n");
  hashtable_print(histo);
  }
  else {
    printf("%s n'est pas dans la table\n", mot);
  }
  puts("---------------");

  // Suppresion de l'element de cle  "Phelma"
  printf("Suprresion de l'entrée associee au mot %s\n","Phelma");
  strcpy(mot,"Phelma");
  if(hashtable_delete_key("Phelma",histo)==1){
  printf("Table \n");
  hashtable_print(histo);
  }
  else {
    printf("%s n'est pas dans la table\n", mot);
  }
  puts("---------------");

  // Suppresion de l'element de cle  "ense3"
  printf("Suprresion de l'entrée associee au mot %s\n","ense3");
  strcpy(mot,"ense3");
  if(hashtable_delete_key("ense3",histo)==1){
  printf("Table \n");
  hashtable_print(histo);
  }
  else {
    printf("%s n'est pas dans la table\n", mot);
  }
  puts("---------------");


  // Liberation memoire; Commenté dans un premier temps.
   hashtable_delete(histo);
}
