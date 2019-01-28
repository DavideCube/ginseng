####COMPILER RELATED####
CC=gcc
CFLAGS=-Wall -Wextra
#######################
######FILENAMES########
OBJ_F=ginseng 
LEX_F=ginseng.l
YACC_F=ginseng.y
#######################
#####SOURCE FILES######
H_DIR=libs
S_DIR=libs
INCL=-I $(wildcard libs/*)
SRCS:=$(wildcard libs/*/*.c)
########################
########OS DETECT#######
OS=$(shell uname -s)
########################

all: $(OBJ_F)

lex.yy.c:
	@echo "Compiling lex file for $(OS) platform..."
ifeq ($(OS), MSYS_NT-10.0)
	@flex $(LEX_F)
else
	@lex $(LEX_F)
endif
	@echo "Lex file compiled!"


y.tab.c:
	@echo "Compiling yacc file $(OS) platform..."
ifeq ($(OS), MSYS_NT-10.0)
	@bison -dy $(YACC_F)
else
	@yacc -d $(YACC_F)
endif
	@echo "Yacc file compiled!"


ginseng: lex.yy.c y.tab.c $(SRCS)
	@echo "Compiling final executable..."
	@$(CC) $(CFLAGS) lex.yy.c y.tab.c $(SRCS) -o $(OBJ_F)
	@echo "Compilation completed!"


.PHONY: clean
clean:
	rm ginseng lex.yy.c y.tab.* 