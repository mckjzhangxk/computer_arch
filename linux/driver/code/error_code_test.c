#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc,char* argv[]){
    int fd=open(argv[1],O_RDWR,0666);
    printf("fd=%d\n",fd);
    int errors[]={EPERM,EINTR,EAGAIN,ENOMEM,EINVAL,EBUSY,EFAULT,ENOTTY,ERESTART};
    int i;
    char buf[64];
    for ( i = 0; i < sizeof(errors)/sizeof(errors[0]); ++i) {
        ioctl(fd,'Z',errors[i]);
        int ret=read(fd,buf,sizeof(buf));
        printf("ioctl %s:%d,read %s:%d,ret=%d\n", strerror(errors[i]),errors[i],strerror(errno),errno,ret);
    }
    return 0;
}