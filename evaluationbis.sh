#!/bin/bash

# Compare les lignes du premier fichier aux lignes du deuxieme fichier
# Retourne 0 si les lignes du du premier fichier se retrouve contineument
# dans le deuxieme fichier
function cmppartialfile() {
  file1=$1;   file2=$2
  declare -a lines2
  declare -a lines1
  size1=0;  size2=0
  while IFS1= read -r line1;  do
    lines1[$size1]=$line1
    size1=`expr $size1 + 1`
  done < $file1
  while IFS2= read -r line2;  do
    lines2[$size2]=$line2
    size2=`expr $size2 + 1`
  done < $file2
  for (( i=0; i<$size2; i++ ));  do
    if [ "${lines2[$i]}" = "${lines1[0]}" ]; then break; fi
  done
  if [ "${lines2[$i]}" = "${lines1[0]}" ]; then
    for (( j=0; j<$size1; j++,i++ ));    do
      if [ "${lines2[$i]}" != "${lines1[$j]}" ]; then
        return 1
      fi
    done
    return 0
  else
    return 1
  fi
}


# Nom des fichiers contenant les resultats attendus
FICRESGRAPH1=resultats/ResultatGraphe1.txt
FICRESGRAPH2=resultats/ResultatGraphe2.txt

# Fichier contenant les resultats de l'execution courante
FIC1=tmp/eval_tmp.txt
# Repertoire des Fichiers contenant les differences ou les erreurs de l'execution courante
FICERR=tmp/tmperr

# Les 3 algos a tester dans l'ordre
ALGOS=("Dijkstra" "BFS" "DFS")

# Nombre de tests reussi et total
reussi=0
nbtotal=0

# Creation des repertoires si necessaire
# Suppression des fichiers existants
if [ ! -d tmp ]; then mkdir tmp; fi
if [ ! -d obj ]; then mkdir obj; fi
if [ ! -d bin ]; then mkdir bin; fi
rm -rf tmp/*
rm -rf obj/*
rm -rf bin/*

######################################
# Test de la compilation de pcc
######################################
FIC="graphes/metro.txt"
TEST=4
echo "\n**********************"
echo "Compilation de bin/metropcc"
nbtotal=`expr $nbtotal + 1 `
make bin/metropcc > /dev/null
if [ $? -eq 0 ];
then
  echo "Compilation bin/pcc OK";
  reussi=`expr $reussi + 1 `;
else
  echo "Erreur de compilation";
fi
######################################
# Test de l'affichage de quelques chemins du metro
######################################
TEST=5
if [ -x bin/metropcc ]; then
  # On efface les resultats precedents
  cat </dev/null > $FIC1
  cat </dev/null > $FICERR"_test"$TEST"_"$algo".txt"
  FICORACLE="resultats/resultatsMetroLaDefense.txt"
  #algo=0    # Affichage des chemins par algo numero 0, ie Dijstra
  algo=0
  echo "Affichage de quelques chemins du metro "$FIC" par "${ALGOS[$algo]}
  for dep in {0..100} ;
    do
      for arr in {0..100};
        do
          if [ -f $FICORACLE ]; then
            cat </dev/null > $FIC1
            echo "Valeur du pcc par "${ALGOS[$algo]}" entre sommets "$dep" et "$arr" sur "$FIC
            bin/metropcc $FIC $algo $dep $arr > $FIC1
            if [ $? -ne 139 ]; then
              cmppartialfile $FIC1 $FICORACLE
              if [ $? -eq 0 ];
              then
                reussi=`expr $reussi + 1 `;
              else
                echo "Erreur Affichage des chemins ${ALGOS[$algo]} entre sommets "$dep" et "$arr" sur "$FIC
                cat  $FICERR"_test"$TEST"_"$algo".txt" $FIC1 > .tmppcc
                mv .tmppcc $FICERR"_test"$TEST"_"$algo".txt"
                echo "Voir fichier "$FICERR"_test"$TEST"_"$algo".txt"
              fi
            fi
          fi
          nbtotal=`expr $nbtotal + 1 `
        done
    done
fi
######################################
# Presence de fichiers de tests
######################################
TEST=6
echo "\n**********************"
nbtests=`grep main \`ls tests/*.c\`| wc -l`
echo "Nombre de fichiers de tests "$nbtests
echo "\n**********************"


echo "Nombre de tests reussi : "$reussi"/"$nbtotal
