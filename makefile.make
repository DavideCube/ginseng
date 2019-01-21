CC=gcc
EXE = dx3
H_DIR = libs
H = $(wildcard $(LIB_DIR)/*/*.h)

all: dx3

dx3: lex.yy.c y.tab.c
	$(CC) lex.yy.c y.tab.c -o dx3