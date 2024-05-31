#include <unistd.h>
#include "stdio.h"
extern char** environ;
int Read(int * p, int size,int fakeNum){
    static int num=2;
    if(fakeNum>0){
        if (num>fakeNum)
        {
            return 0;
        }
        *p=num++;
        return size;
    }else{
        return read(0, p, size);
    }
}
// p = get a number from left neighbor
// print p
// loop:
//     n = get a number from left neighbor
//     if (p does not divide n)
//         send n to right neighbor

// https://swtch.com/~rsc/thread/
int main(int argc, char *argv[])
{
    int maxNum=-1;

    if (argc==2)
    {
        maxNum=35;
        argv[1]=0;
    }

    int p = 0;
    if(Read( &p, 4,maxNum)==0){
        return 0;
    }

    printf("prime %d\n", p);

    char n=p;


    int fd[2];

    pipe(fd);

    int pid = fork();

    if (pid == 0)
    {
        close(0);
        dup(fd[0]);
        close(fd[0]);
        close(fd[1]);

        execve(argv[0],argv,environ);
    }
    else
    {
        close(fd[0]);
        while (( Read( &p, 4,maxNum)>0))
        {
            if (p % n != 0)
            {
                write(fd[1], &p, 4);
            }
        }
        close(fd[1]);

    }

    return 0;
}