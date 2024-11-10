DIRSDL=/usr/local

#############################
# Les sflags de compilation et d'edition des liens
# Linux (dont machine virtuelle phelma)
CFLAGS=-c -g -I ../include -Iinclude -Wall
#CFLAGS=-c -pg -I ../include -Iinclude -Wall
#CFLAGS=-c -I ../include -Iinclude -Wall
LDFLAGS=-lm

############################
# Les repertoires utiles
# Repertoire des sources C contenant les fonctions
SRC_DIR=src
# Repetoire des sources C contenant les programmes demandes
PROG_DIR=prog
# Repertoire des sources C contenant les tests unitaires et intermediaires
TEST_DIR=tests
# Repertoire contenant les .o issus de la compilation
OBJ_DIR=obj
# Repertoire contenant les executables
BIN_DIR=bin
# Repertoire contenant les entetes
INCLUDE_DIR=include

#############################
# Les fichiers a compiler
# Tous les fichiers C contenant les fonctions
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
# Tous les fichiers objets
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Fichiers contenant les progammes : pcc, pcc_all
P1= $(wildcard $(PROG_DIR)/*.c)
EXE_FILES=$(patsubst $(PROG_DIR)/%.c, $(BIN_DIR)/%, $(P1))

# Fichiers contenant les progammes de tests unitaires
P2= $(wildcard $(TEST_DIR)/*.c)
TEST_FILES=$(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/%, $(P2))


##############################
# Les regles
all: $(EXE_FILES) $(TEST_FILES)

# Pour l'edition des liens de pcc
$(BIN_DIR)/metropcc: $(OBJ_DIR)/metropcc.o $(OBJ_FILES)
	gcc  $^ -o $@ $(LDFLAGS)

# Pour l'edition des liens de pcc
$(BIN_DIR)/pcc: $(OBJ_DIR)/pcc.o $(OBJ_FILES)
	gcc  $^ -o $@ $(LDFLAGS)

# Pour l'edition des liens de pcc_all
$(BIN_DIR)/pccall: $(OBJ_DIR)/pccall.o $(OBJ_FILES)
	gcc  $^ -o $@ $(LDFLAGS)

## Pour l'edition des liens de complexite_pcc
$(BIN_DIR)/complexitepcc: $(OBJ_DIR)/complexitepcc.o $(OBJ_FILES)
	gcc  $^ -o $@ $(LDFLAGS)

# Pour les autres programmes, en particulier les tests
# Cette derniere regle efface les .o, bizarre
# alors que les regles explicites ne le font pas.
$(BIN_DIR)/% :  $(OBJ_FILES) $(OBJ_DIR)/%.o
	gcc  $^ -o $@ $(LDFLAGS)

# POur la compilation des fichiers de fonctions
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	gcc $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $(OBJ_DIR)/$*.o

# Pour la compilation des programmes
$(OBJ_DIR)/%.o : $(PROG_DIR)/%.c
	gcc $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@

# pour la compilation des tests
$(OBJ_DIR)/%.o : $(TEST_DIR)/%.c
	gcc $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@

# pour supprimer tous les anciens programmes et autres
clean :
	rm -rf $(OBJ_DIR)/*.o $(OBJ_FILES) $(EXE_FILES) $(TEST_FILES) $(INCLUDE_DIR)/*.gch $(BIN_DIR)/*.dSYM
