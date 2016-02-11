HEADERS = workqueue.h

all: readwrite

readwrite: workqueue.o 
	gcc workqueue.o -o readwrite -lpthread -lm

workqueue.o: workqueue.c ${HEADERS}
	gcc workqueue.c -o workqueue.o

clean:
	-rm -f workqueue.o
	-rm -f 	readwrite
