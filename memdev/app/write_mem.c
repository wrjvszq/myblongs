/*************************************************************************
	> File Name: write_mem.c
	> Author: @wrj
	> Mail: wrjvszq@163.com
	> Created Time: Tue 28 Oct 2014 11:22:01 PM CST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(void)
{
    int fd = 0;
    int test = 123;

    fd = open("/dev/memdev0",O_RDWR);
    write(fd,&test,sizeof(int));
    close(fd);

    return 0;
}
