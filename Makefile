C_SRCS = main.c util.c parse.tab.c lex.yy.c grammar_symbols.c node.c treeprint.c
C_OBJS = $(C_SRCS:%.c=%.o)

CC = gcc
CFLAGS = -g -Wall

%.o : %.c
	$(CC) $(CFLAGS) -c $<

all : jsonparser

jsonparser : $(C_OBJS)
	$(CXX) -o $@ $(C_OBJS)

parse.tab.c : parse.y
	bison -d parse.y

lex.yy.c : lex.l
	flex lex.l

grammar_symbols.h grammar_symbols.c : parse.y scan_grammar_symbols.rb
	./scan_grammar_symbols.rb < parse.y

clean :
	rm -f *.o parse.tab.c lex.yy.c parse.tab.h grammar_symbols.h grammar_symbols.c

depend : grammar_symbols.h grammar_symbols.c parse.tab.c lex.yy.c
	$(CC) $(CFLAFGS) -M $(C_SRCS) > depend.mak

depend.mak :
	touch $@

include depend.mak
