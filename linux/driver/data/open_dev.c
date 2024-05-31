#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc,char argv[]) {
    // 文件路径
    char *file_path = argv[1];

    // 使用 open 函数打开文件，返回文件描述符
    int file_descriptor = open(file_path, O_RDONLY);

    // 检查文件描述符是否有效
    if (file_descriptor == -1) {
        // 打开文件失败，打印错误信息
        perror("Error opening file");
        return errno;
    } else {
        // 打开文件成功，打印文件描述符
        printf("File opened successfully with file descriptor: %d\n", file_descriptor);

        // 在此可以继续对文件进行操作

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
