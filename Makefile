
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/a

SRC= main.c lifegame.c sdlpart.c

# generic build details

CC =     gcc
CFLAGS = -Wall -O
LIBS =   -lSDL2 -lSDL2_image

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< 

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:  main.c lifegame.h sdlpart.h
lifegame.o:  lifegame.c lifegame.h
sdlpart.o: sdlpart.c sdlpart.h

