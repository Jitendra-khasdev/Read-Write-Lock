# gcc -o rw_lock rw_lock.c  workqueue.h -lpthread

HEADERS = workqueue.h
LIBS = -lpthread

all: rw_lock

rw_lock: workqueue.o ${LIBS}
	gcc workqueue.o -o readwrite

workqueue.o: workqueue.c ${HEADERS} ${LIBS}
	gcc workqueue.c -o workqueue.o

clean:
	-rm -f workqueue.o
	-rm -f 	rw_lock
