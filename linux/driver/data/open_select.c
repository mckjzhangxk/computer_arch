#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

int main(){

    fd_set fd_sets;
    int fd= open("/dev/myrw", O_RDONLY|O_NONBLOCK);//需要非阻塞，防止后面read block


    while (1)
    {
        FD_ZERO(&fd_sets);
        FD_SET(fd, &fd_sets);
        int r=select(fd+1,&fd_sets, NULL, NULL, 0);
        if(r<0){
            if (errno==EINTR)
            {
                continue;;
            }else{
                perror("select error");
                break;
            }
        }

        char buf[1024]={0};
        int n=read(fd,buf,sizeof(buf));
        printf("read:%s\n",buf);
    }
    
}