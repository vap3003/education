all : build

build : graph.o translate.o stack.o output.o calc.o
	gcc -o ../build/graph *.o
	rm -f *.o

graph.o : graph.c
	gcc -c -Wall -Werror -Wextra graph.c

translate.o : translate.c
	gcc -c -Wall -Werror -Wextra translate.c

stack.o : stack.c
	gcc -c -Wall -Werror -Wextra stack.c

output.o : output.c
	gcc -c -Wall -Werror -Wextra output.c

calc.o : calc.c
	gcc -c -Wall -Werror -Wextra calc.c

clean :
	rm -rf *.o ../build/graph

rebuild : clean all