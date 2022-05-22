# code details

EXE_DIR = .
EXE = $(EXE_DIR)/a

SRC= test.c

# generic build details

CC =     gcc
CFLAGS = -Wall -O
LIBS =   -lcunit

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

test.o:  test.c

