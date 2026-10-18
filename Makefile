CC = gcc
CFLAGS = -O0 -g -Wall -Wextra -pedantic
LDFLAGS = -lm

TARGETS = wargame_min_max wargame_alpha_beta
COMMON_OBJS = evaluation.o

wargame: $(TARGETS)

all: $(TARGETS)

debug_min_max: wargame_min_max
debug_alpha_beta: wargame_alpha_beta

wargame_min_max: wargame_min_max.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

wargame_alpha_beta: wargame_alpha_beta.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c evaluation.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) *.o

.PHONY: all wargame debug_min_max debug_alpha_beta clean
