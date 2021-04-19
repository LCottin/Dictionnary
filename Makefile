CC=gcc

CFLAGS=-Ofast -march=native -mtune=native -std=c11 -Wall

LDFLAGS=

EXEC=main

SRC=./src/load_dic.c		\
	./src/main-ext.c		\
	./src/anagrammes.c 		\
	./src/palindrome.c 		\
	./src/etoile.c 			\
	./src/question.c 		\
	./src/scrabble.c 		\
	./src/correction.c 		\
	./src/stat_mots.c 		\
	./src/stat_lettres.c 	\
	./src/livre.c



OBJ= $(SRC:.c=.o)

all: $(EXEC)

main: $(OBJ)
	$(CC) $(LDFLAGS) -o ./bin/$@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean mrproper

clean:
	find ./bin -name main -exec rm {} \;
	find ./src -name *.o  -exec rm {} \;

mrproper: clean
	rm $(EXEC)
