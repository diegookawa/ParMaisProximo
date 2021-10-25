all:
	gcc closest.c -o closest -lm

clean:
	rm -f closest;
