run: wargame
	./wargame
wargame: wargame_patron.c
	gcc -o wargame wargame_patron.c
clean:
	rm -f wargame
	clear
.PHONY: clean