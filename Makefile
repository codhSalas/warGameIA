CC = gcc
CFLAGS_DEBUG = -O0 -g -Wall -Wextra -pedantic
LDFLAGS = -flto
TARGETS = wargame_min_max wargame_alpha_beta


wargame: debug_min_max debug_alpha_beta


debug_min_max:
	$(CC) $(CFLAGS_DEBUG) -o wargame_min_max wargame_min_max.c

debug_alpha_beta:
	$(CC) $(CFLAGS_DEBUG) -o wargame_alpha_beta wargame_alpha_beta.c

clean:
	rm -f $(TARGETS) wargame
	clear

.PHONY: clean run debug_min_max debug_alpha_beta
