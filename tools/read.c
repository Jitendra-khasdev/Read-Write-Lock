#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int fd;
	char temp[7];


	fd = open("../shared_resource.txt", O_CREAT | O_RDWR,  0644);

	if (read(fd, temp, 7) > 0)
		printf("Data == %s", temp);
	else
		printf("Error");
	
	close(fd);

	return 0;
}
