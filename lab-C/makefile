all: myshell looper

mypipeline: mypipeline.c
	gcc -m32 -g -Wall -o mypipeline mypipeline.c

myshell: myshell.c LineParser.c LineParser.h
	gcc -m32 -g -Wall -o myshell myshell.c LineParser.c

task1: task1.c
	gcc -m32 -g -Wall -o task1 task1.c

looper: looper.c
	gcc -m32 -g -Wall -o looper looper.c

.PHONY: clean
clean:
	rm -f mypipeline myshell task1 looper