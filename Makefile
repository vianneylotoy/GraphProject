CC=gcc

CFLAGS=-c -Wall 

OBJ=obj/
SRC=src/
LIB=lib/
BIN=bin/
INCLUDE= -I include/


all: executable

executable:	main.o menu.o lliste.o lgraphe.o
	$(CC) -o $(BIN)executable $(OBJ)main.o $(OBJ)menu.o $(OBJ)lliste.o $(OBJ)lgraphe.o

main.o: $(SRC)main.c 
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)main.c -o $(OBJ)main.o 

lliste.o: $(SRC)lliste.c
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)lliste.c -o $(OBJ)lliste.o 

menu.o: $(SRC)menu.c
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)menu.c -o $(OBJ)menu.o 
	

lgraphe.o: $(SRC)lgraphe.c
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)lgraphe.c -o $(OBJ)lgraphe.o 
	
	
# creation de la bibliotheque avec .c et .h

	ar -q $(LIB)libliste.a $(OBJ)lliste.o
	
	ar -q $(LIB)libgraphe.a $(OBJ)lgraphe.o
	
cleanlib:
#	rm -rf $(LIB)*.a	
	
clean:
	rm -rf $(BIN)executable $(OBJ)*.o
	rm -rf $(LIB)*.a
	
run:
	clear
	./$(BIN)executable 
	
debug:
	clear 
#	ulimit -c unlimited
	gdb ./$(BIN)executable core
