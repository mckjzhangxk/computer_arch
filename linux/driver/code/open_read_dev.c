#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc,char* argv[]) {
   
    
    // 使用 open 函数打开文件，返回文件描述符
    int file_descriptor = open("/dev/myrw", O_RDWR);

    // 检查文件描述符是否有效
    if (file_descriptor == -1) {
        // 打开文件失败，打印错误信息
        perror("Error opening file");
        return errno;
    } else {
        // 打开文件成功，打印文件描述符
        printf("File opened successfully with file descriptor: %d\n", file_descriptor);

        // 在此可以继续对文件进行操作
        char buf[100];

        int n=write(file_descriptor,"HELLO\n",7);
        printf("write %d\n",n);
        
        read(file_descriptor,buf,100);
        printf("read %s\n",buf);
        // 关闭文件
        if (close(file_descriptor) == -1) {
            // 关闭文件失败，打印错误信息
            perror("Error closing file");
            return errno;
        } else {
            // 关闭文件成功
            printf("File closed successfully\n");
        }
    }

    return 0;
}
