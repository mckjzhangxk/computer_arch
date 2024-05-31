#include<unistd.h>
#include <fcntl.h>
#include <signal.h>
#include<stdio.h>

int fd;
void xxxx_handler(int signo)
{//读写数据

    printf("recv init signal\n");
}

int main()
{
	fd=open("/dev/myrw",O_RDONLY|O_NONBLOCK);

    //通过fd可以找到pid
	fcntl(fd, F_SETOWN, getpid());
    
    //接受设备的信号
	int oflags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, oflags | FASYNC);

    //信号处理函数
	signal(SIGINT,xxxx_handler);


    while (1)
    {
        /* code */
    }
    
	return 0;
}
    
