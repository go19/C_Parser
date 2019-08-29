all: pointersorter

pointersorter: pointersorter.c
	gcc -g -Wall -Werror -fsanitize=address pointersorter.c -o pointersorter

clean:
	rm -f pointersorter
