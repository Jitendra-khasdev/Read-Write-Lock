#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define SIZE 1024


int main(int argc, char **argv)
{
	int read_fd, write_fd, block;
	char temp[SIZE] = {'\0'};

	if (argc != 3) {
		printf("Can't perform write operation\n");
		exit(1);
	}
	

	read_fd = open(argv[1], O_RDONLY, 644);
	if (read_fd == -1) {
		printf("Can not open read file\n");
		exit(2);
	}
	
	if ((write_fd = creat(argv[2], MODE)) == -1) {
		printf("can not create %s\n", argv[2]);
		exit(3);
	}

	while ((block = read(read_fd, temp, SIZE)) > 0) {
		lseek(write_fd, 1024, SEEK_END);
		if (write(write_fd, temp, block) == -1)
			printf("Error while writing");
	}
	
	return 0;
}
