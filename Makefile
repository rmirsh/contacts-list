CC = gcc
CFLAGS = -Wall -Wextra -std=c11

contacts: main.o contact.o ui.o
	$(CC) $(CFLAGS) -o contacts main.o contact.o ui.o

main.o:    main.c ui.h
contact.o: contact.c contact.h
ui.o:      ui.c ui.h contact.h

clean:
	rm -f *.o contacts
