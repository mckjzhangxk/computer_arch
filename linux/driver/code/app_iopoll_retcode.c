#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#define BLOCK_SIZE 1024
#define MAX_EVENTS 16
#define SELECT_TIME_OUT 5 //seconds

void epoll_add(int epoll_fd, int fd) {
    struct epoll_event e2;
    e2.events =EPOLLIN;//|EPOLLOUT;
    e2.data.fd = fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &e2);
}
// void epoll_addw(int epoll_fd, int fd) {
//     struct epoll_event e2;
//     e2.events = EPOLLOUT;
//     e2.data.fd = fd;
//     epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &e2);
// }

void epoll_del(int epoll_fd, int fd) {
    struct epoll_event e2;
    e2.events = EPOLLIN;
    e2.data.fd = fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &e2);
}

void epoll_mod(int epoll_fd, int fd, int event) {
    struct epoll_event e2;
    e2.events = event;
    e2.data.fd = fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &e2);

}

void set_fd_noblock(int fd) {
    int flag = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

void set_fd_block(int fd) {
    int flag = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flag & ~O_NONBLOCK);
}

int get_socket(char* tsg,int port) {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
    };
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    if(connect(s, (struct sockaddr *)&addr, sizeof(addr))<0){
        printf("connect err\n");
        return -1;
    }
    return s;
}
int main(int argc, char *argv[]) {

    
    // int fd=open(argv[1],O_RDWR,0666);

    int fd=get_socket(argv[1],9000);
    // printf("fd=%d\n",fd);

    int epoll_fd = epoll_create(64);
    if (epoll_fd == -1) {
        printf("create epoll err\n");
        return 0;
    }
    set_fd_noblock(fd);

    epoll_add(epoll_fd, fd);
    // epoll_addw(epoll_fd, fd);
    epoll_mod(epoll_fd, fd, 0);
    // shutdown(fd, SHUT_WR); 
    struct epoll_event events[MAX_EVENTS];
    // HUP,ERR 事件不会被屏蔽
    while (1) {
        int nReady = epoll_wait(epoll_fd, events, MAX_EVENTS, SELECT_TIME_OUT * 1000);

        if(nReady==0){
            printf("timeout \n");
            shutdown(fd, SHUT_WR);// HUP 只有双方都关闭写端才会产生
            continue;
        }
        printf("event occur,nReady %d\n",nReady);

        for (int i = 0; i < nReady; ++i) {
            int fd = events[i].data.fd;
            int ev = events[i].events;

            int isRead = ev & EPOLLIN ? 1 : 0;
            int isWrite = ev & EPOLLOUT ? 1 : 0;
            int isHup = ev & EPOLLHUP ? 1 : 0;
            int isError = ev & EPOLLERR ? 1 : 0;

            printf("[%d],R:%d,W:%d,Hup:%d,Err:%d\n",fd,isRead,isWrite,isHup,isError);

            char buf[1024];
            int r=recv(fd,buf,sizeof(buf),0);
            printf("read %d\n",r);
            // if(r==0){
            //     epoll_mod(epoll_fd, fd, 0);
            //     close(fd);
            // }
        }

    }
    return 0;
}
