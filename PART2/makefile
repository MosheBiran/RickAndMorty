JerryBoree:JerryBoreeMain.o HashTable.o Jerry.o LinkedList.o MultiValueHashTable.o KeyValuePair.o
	gcc JerryBoreeMain.o HashTable.o Jerry.o LinkedList.o MultiValueHashTable.o KeyValuePair.o -o JerryBoree	
JerryBoreeMain.o: JerryBoreeMain.c Defs.h Jerry.h HashTable.h LinkedList.h KeyValuePair.h MultiValueHashTable.h
	gcc -c JerryBoreeMain.c
HashTable.o: HashTable.c HashTable.h Defs.h LinkedList.h KeyValuePair.h
	gcc -c HashTable.c
Jerry.o: Jerry.c Jerry.h Defs.h
	gcc -c Jerry.c
LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c
MultiValueHashTable.o: MultiValueHashTable.c HashTable.h Defs.h LinkedList.h KeyValuePair.h MultiValueHashTable.h
	gcc -c MultiValueHashTable.c
KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c
clean:
	rm -f *.o	
