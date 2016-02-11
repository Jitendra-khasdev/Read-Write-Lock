# gcc -o queue workqueue.c  workqueue.h -lpthread

HEADERS = workqueue.h
LIBS = -lpthread

all: readwrite

readwrite: workqueue.o ${LIBS}
	gcc workqueue.o -o readwrite

workqueue.o: workqueue.c ${HEADERS} ${LIBS}
	gcc workqueue.c -o workqueue.o

clean:
	-rm -f workqueue.o
	-rm -f 	readwrite
