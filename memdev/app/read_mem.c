/*************************************************************************
	> File Name: read_men.c
	> Author: @wrj
	> Mail: wrjvszq@163.com
	> Created Time: Tue 28 Oct 2014 11:29:57 PM CST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(void)
{
    int fd = 0;
    int test = 0;

    fd = open("/dev/memdev0",O_RDWR);
    read(fd,&test,sizeof(int));

    printf("the test is %d\n",test);

    close(fd);
    return 0;
}
