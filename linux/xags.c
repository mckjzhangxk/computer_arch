#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
extern char ** environ;
int main(int argc, char *argv[])
{

    char ch = 0;
    char line[256];
    int index = 0;

    if(argc<2){
        printf("usage xargs command ...");
        return 0;
    }
    while (read(0, &ch, 1) > 0)
    {
        /* code */

        if (ch == '\n')
        {
            /* code */
            line[index++] = 0;

            int pid = fork();

            if (pid == 0)
            {
                char *token = line;
                int new_argc = 1; // number of \0
                while (*token && (token = strchr(token, ' ')))
                {
                    *token = 0;
                    token += 1;
                    new_argc += 1;
                }
                new_argc+=argc-1;//排除argv[0]
                char **new_argv = malloc((new_argc+1)*sizeof(char*));
                //copy argc-1,total argc-2
                for (int i = 1; i < argc; i++)
                {
                    new_argv[i-1] = argv[i];
                }


                int c = argc-1;

                // 0xxxxxxxx
                int i=0;
                if (line[i]==0){
                    while (i<index-1&&line[++i]==0);
                    if(i==index-1){//end of string

                    }else{//非0的位置
                        new_argv[c++] = line +i;
                    }
                } else{
                    new_argv[c++]=line;
                }

                //0a0
                while (i<index)
                {
                    if (line[i] == 0)
                    {
                        while (i<index-1&&line[++i]==0);
                        if(i==index-1){//end of string

                        }else{//非0的位置
                            new_argv[c++] = line +i;
                        }
                    }
                    i++;
                }
                new_argv[c++]=0;
//                for (int i = 0; i < c; i++)
//                {
//                    printf("argv[%d]:%s\n",i,new_argv[i]);
//                }

                execve(new_argv[0], new_argv,environ);
                printf("error\n");
                exit(-1);
            }else{
                wait(0);
            }

            // read new line
            index = 0;
        }
        else
        {
            line[index++] = ch;
        }
    }
    return 0;
}
