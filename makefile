a.out : main.o contact.o
	gcc -o a.out main.o contact.o
main.o : main.c
	gcc -c main.c
contact.o : contact.c
	gcc -c contact.c
clean : 
	rm *.o
