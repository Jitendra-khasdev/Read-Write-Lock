# gcc -o rw_lock rw_lock.c  workqueue.h -lpthread
# gcc -Wall -Werror -pthread rw_lock.c  workqueue.h -o rw_lock


#LIBS = -lpthread


all:
	gcc -Wall -Werror -pthread rw_lock.c  workqueue.h -o rw_lock
clean:
	-rm -f 	rw_lock
	-rm -f  shared_resource.txt
