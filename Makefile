CC = gcc
CFLAGS = -O2 -g -Wall -Wextra -pedantic
INCLUDES = -Iincludes -I.
LDFLAGS = -lm

SRC_DIR = src
INC_DIR = includes
OBJ_DIR = obj

TARGETS = wargame_min_max wargame_alpha_beta

# Modules d'évaluation découpés par thème dans src/
EVAL_SRCS = $(wildcard $(SRC_DIR)/*.c)
EVAL_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(EVAL_SRCS))

HEADERS = $(wildcard $(INC_DIR)/*.h) $(wildcard *.h)

all: $(TARGETS)

wargame: wargame_min_max wargame_alpha_beta

debug_min_max: wargame_min_max
debug_alpha_beta: wargame_alpha_beta

# Création du dossier d'objets
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compilation des modules d'évaluation (src/ -> obj/)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation des fichiers sources racines (. -> obj/)
$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Édition des liens
wargame_min_max: $(OBJ_DIR)/wargame_min_max.o $(EVAL_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

wargame_alpha_beta: $(OBJ_DIR)/wargame_alpha_beta.o $(EVAL_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGETS) *.o

distclean: clean
	rm -rf $(OBJ_DIR)

.PHONY: all wargame debug_min_max debug_alpha_beta clean distclean tournoi run_tournoi ga run_gaCC = gcc
CFLAGS = -O2 -g -Wall -Wextra -pedantic
INCLUDES = -Iincludes -I.
LDFLAGS = -lm

SRC_DIR = src
INC_DIR = includes
OBJ_DIR = obj

TARGETS = wargame_min_max wargame_alpha_beta

# Modules d'évaluation découpés par thème dans src/
EVAL_SRCS = $(wildcard $(SRC_DIR)/*.c)
EVAL_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(EVAL_SRCS))

HEADERS = $(wildcard $(INC_DIR)/*.h) $(wildcard *.h)

all: $(TARGETS)

wargame: wargame_min_max wargame_alpha_beta

debug_min_max: wargame_min_max
debug_alpha_beta: wargame_alpha_beta

# Création du dossier d'objets
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compilation des modules d'évaluation (src/ -> obj/)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation des fichiers sources racines (. -> obj/)
$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Édition des liens
wargame_min_max: $(OBJ_DIR)/wargame_min_max.o $(EVAL_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

wargame_alpha_beta: $(OBJ_DIR)/wargame_alpha_beta.o $(EVAL_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGETS) *.o

distclean: clean
	rm -rf $(OBJ_DIR)

.PHONY: all wargame debug_min_max debug_alpha_beta clean distclean tournoi run_tournoi ga run_ga