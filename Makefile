run: wargame
	./wargame
wargame:wargame_min_max
wargame_min_max: wargame_min_max.c
	gcc -o wargame_min_max wargame_min_max.c
wargame_alpha_beta: wargame_alpha_beta.c
	gcc -o wargame_alpha_beta wargame_alpha_beta.c
clean:
	rm -f wargame wargame_min_max wargame_alpha_beta
	clear
.PHONY: clean