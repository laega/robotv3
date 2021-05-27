#
# Hello Robot C - Makefile des sources du projet.
#
# @author Matthias Brun
#

#
# Organisation des sources.
#

# Packages du projet (à compléter si besoin est).
PACKAGES = commando

# Un niveau de package est accessible.
SRC  = $(wildcard */*.c)
# Pour ajouter un second niveau :		
# SRC += $(wildcard */*/*.c)

OBJ = $(SRC:.c=.o)

# Point d'entrée du programme.
MAIN = main.c

# Gestion automatique des dépendances.
DEP = $(MAIN:.c=.d)

# Exécutable à générer.
EXEC = ../$(PROG)
EXEC_DIR = $(dir $(EXEC))

# Inclusion depuis le niveau du package Robot.
CCFLAGS += -I. -I.. -I./$(PACKAGES) 

#
# Règles du Makefile.
#

# Compilation.
all:
	@for p in $(PACKAGES); do (cd $$p; $(MAKE) $@); done
	@$(MAKE) CCFLAGS="$(CCFLAGS)" LDFLAGS="$(LDFLAGS)" $(EXEC)

$(EXEC): $(OBJ) $(MAIN) | $(EXEC_DIR)
	$(CC) $(CCFLAGS) $(OBJ) $(MAIN) -MF $(DEP) -o $(EXEC) $(LDFLAGS)

$(EXEC_DIR):
	mkdir $@

# Nettoyage.
.PHONY: clean

clean:
	@for p in $(PACKAGES); do (cd $$p; $(MAKE) $@); done
	@rm -f $(DEP)

-include $(DEP)

