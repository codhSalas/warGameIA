CC = gcc
CFLAGS_DEBUG = -O0 -g -Wall -Wextra -pedantic
LDFLAGS = -flto
TARGETS = wargame_min_max wargame_alpha_beta


wargame: debug_min_max debug_alpha_beta


debug_min_max: wargame_min_max.c
	$(CC) $(CFLAGS_DEBUG) -o wargame_min_max wargame_min_max.c -lm

debug_alpha_beta: wargame_alpha_beta.c
	$(CC) $(CFLAGS_DEBUG) -o wargame_alpha_beta wargame_alpha_beta.c -lm

clean:
	rm -f $(TARGETS) wargame
	clear

.PHONY: clean 
