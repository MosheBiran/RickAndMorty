ManageJerries:Jerry.o MainFirst.o
	gcc Jerry.o MainFirst.o -o ManageJerries
Jerry.o: Jerry.c Jerry.h Defs.h
	gcc -c Jerry.c
MainFirst.o: MainFirst.c Defs.h
	gcc -c MainFirst.c
clean:
	rm -f *.o
