all:
	gcc -o test test.c -g

run: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --leak-check=full ./test
